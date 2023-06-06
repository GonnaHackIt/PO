#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "utils.h";

class Context;

class Obstacle {
public:
	unsigned int height;
	Texture::Type texture;
	Point position;

	Obstacle(int height, Point position, Texture::Type texture);
	void render(Context* ctx);
};

class Tree : Obstacle {
public:
	Tree(int height, Point position);
};

class Radiotower : Obstacle {
public:
	Radiotower(int height, Point position);
};

class Map {
public:
	int width, height;
	Texture::Type texture;
	std::vector<Obstacle*> objects;

	Map();
	Map(unsigned int width, unsigned int height);
	static Map load(std::string filename);
	void render(Context* ctx);
	void update(Context* ctx);
};



