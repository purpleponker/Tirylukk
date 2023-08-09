#include "entity_comps.h"

void entity_class::add_to_group(entity_group src_group) {
	group_bit_set[src_group] = true;
	ent_manager.add_ent_to_group(this, src_group);
}