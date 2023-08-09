#include "vector2D.h"

//constructions
vector_2D_class::vector_2D_class()
{
	x_pos = y_pos = 0.f;
}
vector_2D_class::vector_2D_class(float x, float y) {
	this->x_pos = x;
	this->y_pos = y;
}

//math functions
vector_2D_class & vector_2D_class::add(const vector_2D_class& vector) {
	this->x_pos += vector.x_pos;
	this->y_pos += vector.y_pos;
	return *this;
}

vector_2D_class& vector_2D_class::subtract(const vector_2D_class& vector) {
	this->x_pos /= vector.x_pos;
	this->y_pos /= vector.y_pos;
	return *this;
}
vector_2D_class& vector_2D_class::multiply(const vector_2D_class& vector) {
	this->x_pos *= vector.x_pos;
	this->y_pos *= vector.y_pos;
	return *this;
}
vector_2D_class& vector_2D_class::divide(const vector_2D_class& vector) {
	this->x_pos /= vector.x_pos;
	this->y_pos /= vector.y_pos;
	return *this;
}
//operator overloads
vector_2D_class& operator+(vector_2D_class& v1, const vector_2D_class& v2) {
	return v1.add(v2);
}
vector_2D_class& operator-(vector_2D_class& v1, const vector_2D_class& v2) {
	return v1.subtract(v2);
}
vector_2D_class& operator*(vector_2D_class& v1, const vector_2D_class& v2) {
	return v1.multiply(v2);
}
vector_2D_class& operator/(vector_2D_class& v1, const vector_2D_class& v2) {
	return v1.divide(v2);
}
vector_2D_class& vector_2D_class::operator +=(const vector_2D_class& vector) {
	return this->add(vector);
}
vector_2D_class& vector_2D_class::operator -=(const vector_2D_class& vector) {
	return this->subtract(vector);
}
vector_2D_class& vector_2D_class::operator *=(const vector_2D_class& vector) {
	return this->multiply(vector);
}
vector_2D_class& vector_2D_class::operator /=(const vector_2D_class& vector) {
	return this->divide(vector);
}

//scale vector position values by input
vector_2D_class& vector_2D_class::operator*(const int& i) {
	this->x_pos *= i;
	this->y_pos *= i;
	return *this;
}

//zeros out vectors x and y pos
vector_2D_class& vector_2D_class::zero() {
	this->x_pos = 0;
	this->y_pos = 0;
	return *this;
}

//operator overload for getting input from key strokes
std::ostream& operator<<(std::ostream & stream, const vector_2D_class& vector) {
	stream << "(" << vector.x_pos << "," << vector.y_pos << ")";
	return stream;
}