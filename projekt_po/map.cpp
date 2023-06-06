#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "context.h";
#include "utils.h";

Obstacle::Obstacle(int height, Point position, Texture::Type texture) {
	this->height = height;
	this->position = position;
	this->texture = texture;
}
void Obstacle::render(Context* ctx) {
	ctx->textures[(int)this->texture].setPosition(this->position.x - 16, this->position.y - 16);
	ctx->window.draw(ctx->textures[(int)this->texture]);
}

Tree::Tree(int height, Point position) : Obstacle(height, position, Texture::Tree) {

}

Radiotower::Radiotower(int height, Point position) : Obstacle(height, position, Texture::Radiotower) {

}

Map::Map() {
	
}
Map::Map(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	this->texture = Texture::Map;
}
Map Map::load(std::string filename) {
	Map map(1280, 720);
	std::ifstream file(filename);

	if (!file) {
		std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
	}

	int x, y, type;
	while (file >> x >> y >> type) {
		if (type == 0) {
			map.objects.push_back((Obstacle*) new Tree(TREE_HEIGHT, Point(x, y)));
		}
		else if (type == 1) {
			map.objects.push_back((Obstacle*) new Radiotower(TOWER_HEIGHT, Point(x, y)));
		}
	}
	file.close();

	return map;
}
void Map::render(Context* ctx) {
	ctx->textures[(int)this->texture].setPosition(0, 0);
	ctx->window.draw(ctx->textures[(int)this->texture]);

	for (auto obstacle : this->objects) {
		obstacle->render(ctx);
	}
}
void Map::update(Context* ctx) {

}



