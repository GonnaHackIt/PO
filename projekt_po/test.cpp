#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "utils.h"
#include "context.h"
#include "map.h"
#include "radar.h"

TEST(TreeTest, TreeIsInitializedWithCorrectTexture) {
    Tree tree(50, Point(200, 200));

    // Pobieranie tekstury przeszkody
    Texture::Type texture = tree.texture;

    // Oczekujemy, ¿e tekstura przeszkody jest poprawna
    ASSERT_EQ(texture, Texture::Tree);
}

TEST(RadiotowerTest, RadiotowerIsInitializedWithCorrectTexture) {
    Radiotower radiotower(50, Point(200, 200));

    Texture::Type texture = radiotower.texture;

    // Oczekujemy, ¿e tekstura przeszkody jest poprawna
    ASSERT_EQ(texture, Texture::Radiotower);
}

TEST(MapTest, LoadLoadsMapFromFile) {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Font font; // Za³ó¿my, ¿e mamy odpowiedni¹ czcionkê
    Context ctx(Map(), Radar(), 0, font);
    ctx.window = window;

    Map map;
    map = Map::load("map.txt");

    int numObstacles = map.objects.size();

    // Oczekujemy, ¿e liczba przeszkód wynosi 2
    ASSERT_EQ(numObstacles, 2);
}

TEST(MapTest, RenderRendersMapAndObstacles) {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Font font; // Za³ó¿my, ¿e mamy odpowiedni¹ czcionkê
    Context ctx(Map(), Radar(), 0, font);
    ctx.window = window;

    Map map;
    map.objects.push_back((Obstacle*) new Tree(TREE_HEIGHT, Point(200, 200)));
    map.objects.push_back((Obstacle*) new Radiotower(TOWER_HEIGHT, Point(300, 300)));

    // Renderowanie mapy
    map.render(&ctx);
}

TEST(MapTest, UpdateDoesNotThrowErrors) {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    sf::Font font; // Za³ó¿my, ¿e mamy odpowiedni¹ czcionkê
    Context ctx(Map(), Radar(), 0, font);
    ctx.window = window;

    Map map;
    map.update(&ctx);

    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
