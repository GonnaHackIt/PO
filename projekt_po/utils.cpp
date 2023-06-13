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

const char* MapLoadException::what(){ return "B³¹d: Nie uda³o siê za³adowaæ mapy z pliku tekstowego."; }
const char* TextureLoadException::what() { return "B³¹d: Nie uda³o siê za³adowac tekstury."; }
const char* MaxAircraftsExceededException::what() { return "B³¹d: Przekroczono dozwolona liczbe statkow powietrznych."; }