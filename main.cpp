#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "extra.h"
#include "game.h"
#include "sfml.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main() {
    //TODO: Create container for Game objects
    map<string, Game> steamGames;
    // Parse database and create new Game objects
    fstream file("games.csv", ios_base::in);
    //TODO: After container is created, pass container by reference into parseFile() so Game objects can be added to it
    parseFile(file, steamGames);

    // Code for UI
    RenderWindow window(VideoMode(1000, 600), "Steam Game Recommender", sf::Style::Close);

    Font font;
    Event event;
    Text text;
    Texture texture;

    // Sets the font to Arial.
    font.loadFromFile("../files/Arial.ttf");

    // Code for Main Window
    while (window.isOpen()) {
        text.setFont(font);

        // Colors background
        window.clear(Color(26, 42, 61, 0));

        // Sets up side bar
        sf::RectangleShape sideBar(sf::Vector2f(200, 600));
        sideBar.setFillColor(sf::Color(52, 109, 157));
        window.draw(sideBar);


        // Text for Price
        sf::Text priceText = createText("Price", 22, sf::Color::White, sf::Text::Bold);
        priceText.setFont(font);
        setTextCenter(priceText, 100, 25);
        window.draw(priceText);

        // Handles User Interaction with Window
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
        }

        window.display();
    }

    return 0;
};