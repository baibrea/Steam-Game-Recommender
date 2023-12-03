#include "button.h"

Button::Button(string name, int x, int y) {
    this->name = name;
    active = false;
    outerCircle = sf::CircleShape(10.f);
    outerCircle.setFillColor(sf::Color::White);
    innerCircle = sf::CircleShape(8.f);
    innerCircle.setFillColor(sf::Color::Red);
    position = sf::Vector2f(x, y);
    outerCircle.setOrigin(outerCircle.getRadius(), outerCircle.getRadius());
    innerCircle.setOrigin(innerCircle.getRadius(), innerCircle.getRadius());
    outerCircle.setOutlineThickness(3);
    outerCircle.setOutlineColor(sf::Color::Black);
    outerCircle.setPosition(x, y);
    innerCircle.setPosition(x, y);
}

void Button::toggle() {
    cout << "toggled ";
    if (active) {
        active = false;
        cout << "off" << endl;
    }
    else {
        active = true;
        cout << "on" << endl;
    }
}

void Button::drawButton(sf::RenderWindow& window) {
    window.draw(outerCircle);
    if (this->active) {
        window.draw(innerCircle);
    }
}

sf::FloatRect Button::getBounds() {
    sf::FloatRect bounds = outerCircle.getGlobalBounds();
    return bounds;
}
