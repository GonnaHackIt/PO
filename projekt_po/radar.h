#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "utils.h";

class Context;

class FlightPath {
public:
	Point from, to;

	FlightPath();
	FlightPath(Point from, Point to);
	void update(Point from, Point to);
};

class Aircraft {
public:
	Point position;
	unsigned int max_altitude;
	Texture::Type texture;
	FlightPath path;
	std::string name;
	unsigned int velocity;

	Aircraft(Point position, unsigned int altitude, FlightPath path, std::string name, unsigned int velocity, Texture::Type texture);
	void update();
	bool check_collision(Context* ctx, int id);
	int altitude();
	virtual void render(Context* ctx, int id);
};


class Plane : Aircraft {
public:
	Plane(Point position, FlightPath path, std::string name);
	void render(Context* ctx, int id);
};

class Balloon : Aircraft {
public:
	Balloon(Point position, FlightPath path, std::string name);
};

class Helicopter : Aircraft {
public:
	Helicopter(Point position, FlightPath path, std::string name);
	void render(Context* ctx, int id);
};

class Glider : Aircraft {
public:
	Glider(Point position, FlightPath path, std::string name);
	void render(Context* ctx, int id);
};

class Radar {
public:
	std::vector<Aircraft*> aircrafts;

	Radar();
	void render(Context* ctx);
	void update(Context* ctx);
};