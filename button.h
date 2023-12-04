#include <iostream>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;

class Button {
private:
    string name;
    sf::CircleShape outerCircle;
    sf::CircleShape innerCircle;
    sf::Vector2f position;
    bool active;
public:
    Button(string name, int x, int y);
    void toggle();
    void drawButton(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    bool isActive();
    string getName();
};