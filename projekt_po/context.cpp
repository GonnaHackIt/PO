#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "utils.h";
#include "context.h";
#include "map.h";
#include "radar.h";

Button::Button() {

}
Button::Button(unsigned int width, unsigned int height, Point position, std::string text, Context* ctx) {
	this->width = width;
	this->height = height;
	this->position = position;
	this->texture = Texture::Button;
	this->text.setFont(ctx->font);
	this->text.setCharacterSize(36);
	this->text.setFillColor(sf::Color::Red);
	this->text.setString(text);
	this->text.setPosition(position.x + 16, position.y + 8);
}
bool Button::is_clicked(Context* ctx) {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(ctx->window);

	if (mouse_pos.x >= this->position.x && 
		mouse_pos.x <= this->position.x + this->width && 
		mouse_pos.y >= this->position.y && 
		mouse_pos.y <= this->position.y + this->height) 
	{
		return true;
	}
	return false;
}
void Button::render(Context* ctx) {
	ctx->textures[(int)this->texture].setPosition(this->position.x, this->position.y);
	ctx->window.draw(ctx->textures[(int)this->texture]);
	ctx->window.draw(this->text);
}

TextArea::TextArea() {

}
TextArea::TextArea(Context* ctx) {
	this->text.setFont(ctx->font);
	this->text.setCharacterSize(15);
	this->text.setFillColor(sf::Color::Red);
	this->position = Point(800, 800);
}
void TextArea::render(Context* ctx) {
	text.setString("Selected: " + choices[ctx->choice]);

	ctx->window.draw(text);
}
void TextArea::update(Context* ctx) {

}

Menu::Menu() {
	
}

void Menu::init(Context* ctx) {
	for (int i = 0; i < 4; i++) {
		Button b(256, 64, Point(2 + (256 + 84) * i, 720 - 64 - 2), choices[i], ctx);
		this->buttons.push_back(b);
	}
}

void Menu::render(Context* ctx) {
	for (auto button : this->buttons) {
		button.render(ctx);
	}
	this->description.render(ctx);
}

bool Menu::clicked(Context* ctx) {
	for (int i = 0; i < this->buttons.size(); i++) {
		if (this->buttons[i].is_clicked(ctx)) {
			for (int j = 0; j < this->buttons.size(); j++) {
				if (i == j) {
					this->buttons[j].texture = Texture::ButtonPressed;
					continue;
				}
				this->buttons[j].texture = Texture::Button;
			}
			ctx->choice = i;
			ctx->selected = -1;
			return true;
		}
	}
	return false;
}

Context::Context(Map map, Radar radar, int choice, sf::Font font) {
	this->map = map;
	this->radar = radar;
	this->choice = choice;
	this->menu.init(this);
	this->name = name;
	this->selected = -1;
	this->font = font;
	this->window.create(sf::VideoMode(1280, 720), "Radar Lotów");
	this->window.setFramerateLimit(100);
	this->frame = 0;

	this->altitude_meter.setFont(this->font);
	this->altitude_meter.setCharacterSize(36);
	this->altitude_meter.setFillColor(sf::Color::Red);
	this->altitude_meter.setPosition(1200, 10);

	for (int i = 0; i < NUM_TEXTURES; i++) {
		sf::Image* image = new sf::Image();

		if (!image->loadFromFile("Textures/" + std::to_string(i) + ".png"))
			throw TextureLoadException();

		sf::Texture* texture = new sf::Texture();
		texture->loadFromImage(*image);

		sf::Sprite sprite;
		sprite.setTexture(*texture, true);

		this->textures.push_back(sprite);
	}
}

void Context::render() {
	this->window.clear();
	
	this->map.render(this);
	this->menu.render(this);
	this->radar.render(this);
	if (selected != -1) {
		int altitude = this->radar.aircrafts[this->selected]->altitude();
		this->altitude_meter.setString(std::to_string(altitude));
		this->window.draw(altitude_meter);
	}

	this->window.display();
}

void Context::update() {
	this->map.update(this);
	this->radar.update(this);
}

void Context::run() {
	while (this->window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (!this->menu.clicked(this) && selected == -1 && choice != -1) {
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
					Point position(mouse_pos.x, mouse_pos.y);

					for (int i = 0; i < radar.aircrafts.size(); i++) {
						Aircraft* aircraft = radar.aircrafts[i];
						if (dist(position, aircraft->position) <= HITBOX_RADIUS) {
							selected = i;
							goto render;
						}
					}

					FlightPath path(position, position);
					Aircraft* new_aircraft = nullptr;

					switch (choice) {
					case 0:
						new_aircraft = (Aircraft*) new Plane(position, path, std::to_string(name++));
						break;
					case 1:
						new_aircraft = (Aircraft*) new Balloon(position, path, std::to_string(name++));
						break;
					case 2:
						new_aircraft = (Aircraft*) new Helicopter(position, path, std::to_string(name++));
						break;
					case 3:
						new_aircraft = (Aircraft*) new Glider(position, path, std::to_string(name++));
						break;
					}

					
					try {
						radar.add_aircraft(new_aircraft);
						selected = radar.aircrafts.size() - 1;
					}
					catch (MaxAircraftsExceededException error)
					{
						std::cout << error.what() << std::endl;
					}
				}
				else if (selected != -1) {
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
					Point position(mouse_pos.x, mouse_pos.y);

					Aircraft* aircraft = radar.aircrafts[selected];

					aircraft->path.update(aircraft->position, position);
					selected = -1;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				selected = -1;
			}
		}
	render:
		this->render();
		
	update:
		this->update();

		this->frame++;
	}
}
