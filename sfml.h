#include <iostream>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;

sf::Text createText(string text, int size, sf::Color color, sf::Text::Style style);

void setTextCenter(sf::Text& text, float x, float y);

