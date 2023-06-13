#include "radar.h";
#include "map.h";
#include "context.h";
#include <iostream>;

int main()
{
    Map map;
    try {
        map = Map::load("map.txt");
    }
    catch (MapLoadException error)
    {
        std::cout << error.what() << std::endl;
    }

    Radar radar;
    sf::Font font;
    if (!font.loadFromFile("Consolas.ttf")) {
        return 10;
    }


    try {
        Context ctx(map, radar, -1, font);
        ctx.run();
    }
    catch (TextureLoadException error)
    {
        std::cout << error.what() << std::endl;
    }

    return 0;
}