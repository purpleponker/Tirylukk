#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class component_class;
class entity_class;
class ent_man_class;

using component_id = std::size_t;
using entity_group = std::size_t;


//inline funcs to get entity ids
inline component_id get_new_component_type_id() {
	static component_id previous_id = 0u;
	return previous_id++;
}

template <typename T> inline component_id get_component_type_id() noexcept {
	static component_id type_id = get_new_component_type_id();
	return type_id;
}

//limit enitities and entity groups sizing
//for render layers and collision layers, allowing entities to exist in multiple groupings
constexpr std::size_t max_components = 32;
constexpr std::size_t max_group_size = 32;

using component_bit_set = std::bitset<max_components>;
using grouping_bit_set = std::bitset<max_group_size>;
using component_array = std::array<component_class*, max_components>;

//comp class to hold entities
class component_class {
public:
	entity_class* entity = NULL;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~component_class() {}
private:
};

//define entities in game
class entity_class {
public:
	entity_class(ent_man_class & ent_manager_src) : ent_manager(ent_manager_src){}

	void update() {
		for (auto& c : component_list) c->update();
	}
	void draw() {
		for (auto& c : component_list) c->draw();
	}
	bool is_active() { return active; }

	bool is_in_group(entity_group src_group) {
		return group_bit_set[src_group];
	}
	void add_to_group(entity_group src_group);
	void remove_from_group(entity_group src_group) {
		group_bit_set[src_group] = false;
	}

	//set avtivity to false to envoke destruction
	void destroy() { active = false; }

	template < typename T> bool has_component() const {
		return comp_bit_set[get_component_type_id<T>()];
	}

	template <typename T, typename... TArgs>
	T& add_component(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<component_class> uPtr{ c };
		component_list.emplace_back(std::move(uPtr));

		comp_array[get_component_type_id<T>()] = c;
		comp_bit_set[get_component_type_id<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& get_component() const {
		auto ptr(comp_array[get_component_type_id<T>()]);
		return *static_cast<T*>(ptr);
	}


private:
	ent_man_class & ent_manager;
	bool active = true;
	std::vector<std::unique_ptr<component_class>> component_list;

	component_array comp_array = {};
	component_bit_set comp_bit_set;
	grouping_bit_set group_bit_set;
};

//manage entity properties
class ent_man_class {
public:
	void update() {
		for (auto& e : entity_list) e->update();
	}
	void draw() {
		for (auto& e : entity_list) e->draw();
	}

	//update grouped entities and active enities
	void refresh() {
		for (auto i(0u); i < max_group_size; i++) {
			auto& list(grouped_entities[i]);
			list.erase(std::remove_if(std::begin(list), std::end(list), [i](entity_class* src_entity)
				{
					return !src_entity->is_active() || !src_entity->is_in_group(i);
				}), std::end(list));
		}

		entity_list.erase(std::remove_if(std::begin(entity_list), std::end(entity_list),
			[](const std::unique_ptr<entity_class>& m_entity)
			{
				return !m_entity->is_active();
			}),
			std::end(entity_list));
	}

	void add_ent_to_group(entity_class* src_entity, entity_group src_group) {
		grouped_entities[src_group].emplace_back(src_entity);
	}

	std::vector<entity_class*>& get_group(entity_group src_group) {
		return grouped_entities[src_group];
	}

	entity_class& add_entity() {
		entity_class* e = new entity_class(*this);
		std::unique_ptr<entity_class> uPtr{ e };
		entity_list.emplace_back(std::move_if_noexcept(uPtr));
		return * e;
	}

private:
	std::vector<std::unique_ptr<entity_class>> entity_list;
	std::array<std::vector<entity_class*>, max_group_size> grouped_entities;
};
