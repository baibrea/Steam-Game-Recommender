#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "game.h"
#pragma once
using namespace std;

sf::Text createText(string text, int size, sf::Color color);

void setTextCenter(sf::Text& text, float x, float y);

void leftMouseClick(int x, int y, vector<Button>& buttons);

bool clickedSearchBar(sf::RectangleShape bounds, sf::Vector2i mousePosition);

sf::RectangleShape createTitleBox(int y);
