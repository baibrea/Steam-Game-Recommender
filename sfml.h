#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
#pragma once
using namespace std;

sf::Text createText(string text, int size, sf::Color color);

void setTextCenter(sf::Text& text, float x, float y);

void leftMouseClick(int x, int y, vector<Button>& buttons);

