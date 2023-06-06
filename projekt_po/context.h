#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "utils.h";
#include "map.h";
#include "radar.h";

class Button {
public:
	unsigned int width, height;
	Texture::Type texture;
	sf::Text text;
	Point position;

	Button();
	Button(unsigned int height, unsigned int width, Point position, std::string text, Context* ctx);
	bool is_clicked(Context* ctx);
	void render(Context* ctx);
};

class TextArea {
public:
	sf::Text text;
	Point position;

	TextArea();
	TextArea(Context* ctx);
	void render(Context* ctx);
	void update(Context* ctx);
};

class Menu {
public:
	std::vector<Button> buttons;
	TextArea description;

	Menu();
	void init(Context* ctx);
	void render(Context* ctx);
	bool clicked(Context* ctx);
};

class Context {
public:
	Map map;
	Radar radar;
	Menu menu;
	int choice;
	int name;
	int selected;
	sf::RenderWindow window;
	sf::Font font;
	std::vector<sf::Sprite> textures;
	unsigned int frame;
	sf::Text altitude_meter;

	Context(Map map, Radar radar, int choice, sf::Font font);
	void render();
	void update();
	void run();
};