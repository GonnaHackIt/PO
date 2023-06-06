#include "radar.h";
#include "map.h";
#include "context.h";

int main()
{
    Map map = Map::load("map.txt");
    Radar radar;
    sf::Font font;
    if (!font.loadFromFile("Consolas.ttf")) {
        return 10;
    }

    Context ctx(map, radar, -1, font);
    ctx.run();

    return 0;
}