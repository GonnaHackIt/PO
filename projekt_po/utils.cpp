#include "utils.h"

#include <exception>
#include <string>

Point::Point() {}
Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}
Point Point::operator-(Point point) {
	Point new_point(this->x - point.x, this->y - point.y);

	return new_point;
}
Point Point::operator+(Point point) {
	Point new_point(this->x + point.x, this->y + point.y);

	return new_point;
}
void Point::operator+=(Point point) {
	this->x += point.x;
	this->y += point.y;
}

float dist(Point a, Point b) {
	Point c = b - a;
	return sqrt(pow(c.x, 2) + pow(c.y, 2));
}

const char* MapLoadException::what(){ return "B��d: Nie uda�o si� za�adowa� mapy z pliku tekstowego."; }
const char* TextureLoadException::what() { return "B��d: Nie uda�o si� za�adowac tekstury."; }
const char* MaxAircraftsExceededException::what() { return "B��d: Przekroczono dozwolona liczbe statkow powietrznych."; }