#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "game.h"
#pragma once
using namespace std;

sf::Text createText(string text, int size, sf::Color color);

void setTextCenter(sf::Text& text, float x, float y);

void leftMouseClickButton(int x, int y, vector<Button>& buttons);

int leftMouseClickTitle(int x, int y, vector<sf::RectangleShape>& titleBoxes);

bool clickedSearchBar(sf::RectangleShape bounds, sf::Vector2i mousePosition);

sf::RectangleShape createTitleBox(int y);
