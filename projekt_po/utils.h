#pragma once

#include <string>

constexpr double PI = 3.141592653589793238462643;
constexpr unsigned int NUM_TEXTURES = 9;
constexpr unsigned int TREE_HEIGHT = 100;
constexpr unsigned int TOWER_HEIGHT = 1000;

constexpr unsigned int PLANE_ALTITUDE = 10000;
constexpr unsigned int PLANE_VELOCITY = 250;

constexpr unsigned int BALLOON_ALTITUDE = 500;
constexpr unsigned int BALLOON_VELOCITY = 1;

constexpr unsigned int HELICOPTER_ALTITUDE = 1000;
constexpr unsigned int HELICOPTER_VELOCITY = 100;

constexpr unsigned int GLIDER_ALTITUDE = 1500;
constexpr unsigned int GLIDER_VELOCITY = 20;

constexpr unsigned int HITBOX_RADIUS = 42; //32sqrt(2)
constexpr unsigned int COLLISION_RADIUS = 64;
constexpr float SIMULATION_VELOCITY = (float)1 / 1000;

static std::string choices[4] = { "Plane", "Balloon", "Helicopter", "Glider" };

struct Texture {
	enum Type {
		Map,
		Balloon,
		Button,
		ButtonPressed,
		Helicopter,
		Plane,
		Glider,
		Tree,
		Radiotower,
	};
};

class Point { 
public:
	float x, y;

	Point();
	Point(float x, float y);
	Point operator-(Point point);
	Point operator+(Point point);
	void operator+=(Point point);
};

float dist(Point a, Point b);