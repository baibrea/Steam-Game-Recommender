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

void leftMouseClickButton(int x, int y, vector<Button>& buttons) {
    if (x < 200) {
        for (int i = 0; i < buttons.size(); i++) {
            sf::FloatRect bounds = buttons.at(i).getBounds();
            if (bounds.contains(x, y)) {
                for (int j = 0; j < buttons.size(); j++) {
                    if (buttons.at(j).isActive()) {
                        buttons.at(j).toggle();
                    }
                }
                buttons.at(i).toggle();
                break;
            }
        }
    }
}
int leftMouseClickTitle(int x, int y, vector<sf::RectangleShape>& titleBoxes) {
    for (int i = 0; i < 14; i++) {
        sf::FloatRect bounds = titleBoxes.at(i).getGlobalBounds();
        if (bounds.contains(x, y)) {
            return i;
        }
    }
}


bool clickedSearchBar(sf::RectangleShape bounds, sf::Vector2i mousePosition) {
    if (bounds.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
        return true;
    else
        return false;
}

sf::RectangleShape createTitleBox(int y) {
    sf::RectangleShape titleBox(sf::Vector2f(750, 34));
    titleBox.setFillColor(sf::Color(37, 78, 110));
    sf::FloatRect bounds = titleBox.getLocalBounds();
    titleBox.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
    titleBox.setPosition(600, y);
    titleBox.setOutlineThickness(0.5);
    titleBox.setOutlineColor(sf::Color::White);
    return titleBox;
}
