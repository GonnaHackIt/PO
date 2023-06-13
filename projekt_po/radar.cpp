#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "context.h";
#include "utils.h";


FlightPath::FlightPath() {

}
FlightPath::FlightPath(Point from, Point to) {
	this->from = from;
	this->to = to;
}
void FlightPath::update(Point from, Point to) {
	this->from = from;
	this->to = to;
}

Aircraft::Aircraft(Point position, unsigned int max_altitude, FlightPath path, std::string name, unsigned int velocity, Texture::Type texture) {
	this->position = position;
	this->max_altitude = max_altitude;
	this->path = path;
	this->name = name;
	this->velocity = velocity;
	this->texture = texture;
}

void Aircraft::update() {
	Point direction = this->path.to - this->position;

	float scalar = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	if (scalar <= 1) {
		scalar = 1;
	}

	direction.x *= this->velocity * SIMULATION_VELOCITY / scalar;
	direction.y *= this->velocity * SIMULATION_VELOCITY / scalar;

	this->position += direction;
}

bool Aircraft::check_collision(Context* ctx, int id) {
	for (int i = 0; i < ctx->radar.aircrafts.size(); i++) {
		for (int j = 0; j < ctx->map.objects.size(); j++) {
			Obstacle* object = ctx->map.objects[j];
			if (dist(this->position, object->position) <= COLLISION_RADIUS && this->altitude() <= object->height + 500) {
				return true;
			}
		}

		if (i == id) continue;

		Aircraft* aircraft = ctx->radar.aircrafts[i];

		if (dist(this->position, aircraft->position) <= COLLISION_RADIUS && fabs(aircraft->altitude() - this->altitude()) <= 500) {
			return true;
		}
	}

	return false;
}

int Aircraft::altitude() {
	if (dist(this->path.from, this->path.to) == 0) {
		return 0;
	}
	float ratio = dist(this->path.from, this->position) / dist(this->path.from, this->path.to);
	
	return sin(PI * ratio) * this->max_altitude;
}

void Aircraft::render(Context* ctx, int id) {
	sf::Color color(0, 0, 0, 0);
	if (id == ctx->selected) {
		color = sf::Color::Yellow;
	}
	else if (this->check_collision(ctx, id)) {
		color = sf::Color::Red;
	}

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(32, 32));
	rect.setPosition(this->position.x - 16, this->position.y - 16);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(color);
	rect.setOutlineThickness(3);
	ctx->window.draw(rect);
	
	ctx->textures[(int)this->texture].setPosition(this->position.x - 16, this->position.y - 16);
	ctx->window.draw(ctx->textures[(int)this->texture]);

}

Plane::Plane(Point position, FlightPath path, std::string name) :
	Aircraft(position, PLANE_ALTITUDE, path, name, PLANE_VELOCITY, Texture::Plane) {

}

void Plane::render(Context* ctx, int id) {
	sf::Color color(0, 0, 0, 0);
	if (id == ctx->selected) {
		color = sf::Color::Yellow;
	}
	else if (this->check_collision(ctx, id)) {
		color = sf::Color::Red;
	}

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(32, 32));
	rect.setPosition(this->position.x - 16, this->position.y - 16);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(color);
	rect.setOutlineThickness(3);
	ctx->window.draw(rect);

	Point direction = this->path.to - this->position;
	sf::Transform transform;
	transform.translate(this->position.x - 16, this->position.y - 16);
	transform.rotate(180 * atan2(direction.y, direction.x) / 3.1415 + 90, 16, 16);
	

	ctx->textures[(int)this->texture].setPosition(0, 0);
	ctx->window.draw(ctx->textures[(int)this->texture], transform);
}

Balloon::Balloon(Point position, FlightPath path, std::string name) :
	Aircraft(position, BALLOON_ALTITUDE, path, name, BALLOON_VELOCITY, Texture::Balloon) {

}

Helicopter::Helicopter(Point position, FlightPath path, std::string name) :
	Aircraft(position, HELICOPTER_ALTITUDE, path, name, HELICOPTER_VELOCITY, Texture::Helicopter) {

}

void Helicopter::render(Context* ctx, int id) {
	sf::Color color(0, 0, 0, 0);
	if (id == ctx->selected) {
		color = sf::Color::Yellow;
	}
	else if (this->check_collision(ctx, id)) {
		color = sf::Color::Red;
	}

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(32, 32));
	rect.setPosition(this->position.x - 16, this->position.y - 16);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(color);
	rect.setOutlineThickness(3);
	ctx->window.draw(rect);

	Point direction = this->path.to - this->position;

	if (direction.x > 0) {
		ctx->textures[(int)this->texture].setScale(-1, 1);
		ctx->textures[(int)this->texture].setPosition(this->position.x + 16, this->position.y - 16);
	}
	else {
		ctx->textures[(int)this->texture].setScale(1, 1);
		ctx->textures[(int)this->texture].setPosition(this->position.x - 16, this->position.y - 16);
	}
	
	ctx->window.draw(ctx->textures[(int)this->texture]);
}

Glider::Glider(Point position, FlightPath path, std::string name) :
	Aircraft(position, GLIDER_ALTITUDE, path, name, GLIDER_VELOCITY, Texture::Glider) {

}

void Glider::render(Context* ctx, int id) {
	sf::Color color(0, 0, 0, 0);
	if (id == ctx->selected) {
		color = sf::Color::Yellow;
	}
	else if (this->check_collision(ctx, id)) {
		color = sf::Color::Red;
	}

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(32, 32));
	rect.setPosition(this->position.x - 16, this->position.y - 16);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(color);
	rect.setOutlineThickness(3);
	ctx->window.draw(rect);

	Point direction = this->path.to - this->position;
	sf::Transform transform;
	transform.translate(this->position.x - 16, this->position.y - 16);
	transform.rotate(180 * atan2(direction.y, direction.x) / 3.1415 + 90, 16, 16);


	ctx->textures[(int)this->texture].setPosition(0, 0);
	ctx->window.draw(ctx->textures[(int)this->texture], transform);
}

Radar::Radar() {

}
void Radar::render(Context* ctx) {
	for (int i = 0; i < this->aircrafts.size(); i++) {
		aircrafts[i]->render(ctx, i);
	}
}
void Radar::update(Context* ctx) {
	for (auto aircraft : aircrafts) {
		aircraft->update();
	}
}
void Radar::add_aircraft(Aircraft* aircraft)
{
	int maxAircrafts = 15; //to mo¿e byc zmienione
	if (this->aircrafts.size() >= maxAircrafts)
	{
		throw MaxAircraftsExceededException();
	}
	this->aircrafts.push_back(aircraft);
}