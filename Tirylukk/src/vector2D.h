#pragma once

#include <vector>
#include <iostream>

class vector_2D_class {
public:
	float x_pos;
	float y_pos;
	vector_2D_class();
	vector_2D_class(float x, float y);
	vector_2D_class& add(const vector_2D_class & vector);
	vector_2D_class& subtract(const vector_2D_class& vector);
	vector_2D_class& multiply(const vector_2D_class& vector);
	vector_2D_class& divide(const vector_2D_class& vector);
	vector_2D_class& inverse(const vector_2D_class& vector);

	friend vector_2D_class & operator+(vector_2D_class& v1, const vector_2D_class& v2);
	friend vector_2D_class & operator-(vector_2D_class& v1, const vector_2D_class& v2);
	friend vector_2D_class & operator*(vector_2D_class& v1, const vector_2D_class& v2);
	friend vector_2D_class & operator/(vector_2D_class& v1, const vector_2D_class& v2);

	vector_2D_class & operator +=(const vector_2D_class& vector);
	vector_2D_class & operator -=(const vector_2D_class& vector);
	vector_2D_class & operator *=(const vector_2D_class& vector);
	vector_2D_class & operator /=(const vector_2D_class& vector);

	vector_2D_class& operator*(const int& i);
	vector_2D_class& zero();

	friend std::ostream& operator<<(std::ostream, const vector_2D_class& vector);
private:
};
