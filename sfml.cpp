#include "sfml.h"
using namespace std;

sf::Text createText(string text, int size, sf::Color color) {
    sf::Text newText;
    newText.setString(text);
    newText.setCharacterSize(size);
    newText.setFillColor(color);
    return newText;
}

void setTextCenter(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(x, y);
}
