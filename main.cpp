#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "extra.h"
#include "game.h"
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
        window.clear(Color(26, 42, 61, 0));

        // Text for Price
        text.setFillColor(Color(255, 255, 255, 255));
        text.setString("Price");
        text.setCharacterSize(16);
        text.setStyle(Text::Bold);
        text.setPosition(0, 0);
        window.draw(text);

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