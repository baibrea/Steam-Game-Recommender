#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "extra.h"
#include "game.h"
#include "sfml.h"
#include "button.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main() {
    // Create containers (Game objects, buttons)
    map<string, Game> steamGames;

    // Parse database and create new Game objects
    fstream file("games.csv", ios_base::in);
    //TODO: After container is created, pass container by reference into parseFile() so Game objects can be added to it
    parseFile(file, steamGames);

    // Extra array for sorting
    cout << steamGames.size();
    vector<Game> arr;
    for(auto &game: steamGames) {
        arr.push_back(game.second);
    }
//     Running QuickSort
    quickSort(arr, 0, arr.size()-1, "peakCCU");
    for(int i = 0; i < arr.size(); i++) {
        cout << "Game: " << arr.at(i).getTitle() << " Peak CCU: " << arr.at(i).getPeakCCU() << endl;
    }


    // Code for UI
    // Create window
    RenderWindow window(VideoMode(1000, 600), "Steam Game Recommender", sf::Style::Close);

    // Sets the font to Arial
    Font font;
    font.loadFromFile("../files/Arial.ttf");
    bool textEntered = false;
    string searchString = "|";

    Event event;

    // Sets up side bar
    sf::RectangleShape sideBar(sf::Vector2f(200, 600));
    sideBar.setFillColor(sf::Color(52, 109, 157));
    sideBar.setOutlineThickness(4);
    sideBar.setOutlineColor(sf::Color::White);

    // Text for "Steam Game Recommender"
    // FIXME: I don't know if this looks good or not so this can be removed later
    sf::Text titleText1 = createText("STEAM GAME", 22, sf::Color::White);
    sf::Text titleText2 = createText("RECOMMENDER", 22, sf::Color::White);
    titleText1.setStyle(sf::Text::Bold);
    titleText2.setStyle(sf::Text::Bold);
    titleText1.setFont(font);
    titleText2.setFont(font);
    setTextCenter(titleText1, 100, 50);
    setTextCenter(titleText2, 100, 80);

    // Text for Price
    sf::Text priceText = createText("Price", 22, sf::Color::White);
    priceText.setStyle(sf::Text::Bold);
    priceText.setFont(font);
    setTextCenter(priceText, 100, 25);

    // Textbox for game search
    sf::RectangleShape searchBox(sf::Vector2f(750, 40));
    searchBox.setFillColor(sf::Color(37, 78, 110));
    sf::FloatRect rectBounds = searchBox.getLocalBounds();
    searchBox.setOrigin(rectBounds.left + rectBounds.width/2.0f, rectBounds.top + rectBounds.height/2.0f);
    searchBox.setPosition(600, 40);
    searchBox.setOutlineThickness(4);
    searchBox.setOutlineColor(sf::Color::White);

    // Default "search" text in search box
    sf::Text searchText = createText("search", 24, sf::Color(192, 192, 192));
    searchText.setFont(font);
    searchText.setPosition(240, 25);

    // Box to display game titles/game information
    sf::RectangleShape gameBox(sf::Vector2f(750, 490));
    gameBox.setFillColor(sf::Color(37, 78, 110));
    sf::FloatRect bounds = gameBox.getLocalBounds();
    gameBox.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
    gameBox.setPosition(600, 330);
    gameBox.setOutlineThickness(4);
    gameBox.setOutlineColor(sf::Color::White);

    // Create buttons
    vector<Button> buttons{};
    Button priceButton("price", 25, 150);
    buttons.push_back(priceButton);
    bool typing = false;

    // Code for Main Window
    while (window.isOpen()) {

        // Handles User Interaction with Window
        char input;
        Vector2i mousePosition;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // If user closes window, close
                case Event::Closed:
                    window.close();
                    break;

                // If user enters text, append characters to search box text
                case Event::TextEntered:
                    if (typing == true) {
                        input = static_cast<char>(event.text.unicode);
                        if (31 < event.text.unicode && event.text.unicode < 128) {
                            textEntered = true;
                            searchString.pop_back();
                            searchString.push_back(input);
                            searchString.push_back('|');
                            cout << searchString << endl;
                        }
                    }
                    break;
                case Event::KeyPressed:
                    // If user presses backspace, delete the last character in the search bar
                    if (typing == true) {
                        if (event.key.code == sf::Keyboard::Backspace and searchString.size() > 1) {
                            searchString.pop_back();
                            searchString.pop_back();
                            searchString.push_back('|');
                            cout << searchString << endl;
                        }
                        if (searchString.size() == 1) {
                            textEntered = false;
                        }
                    }
                    // TODO: If user presses enter, search for current string in game titles (ignore case sensitivity)
                    break;
                case Event::MouseButtonPressed:
                    sf::Mouse mouse;
                    sf::Vector2i mousePosition = mouse.getPosition(window);
                    int x = mousePosition.x;
                    int y = mousePosition.y;
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //
                        leftMouseClick(x, y, buttons);

                        if (searchBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            typing = true;
                            if (searchString == "|")
                                textEntered = true;
                        }

                        else
                            typing = false;
                    }
                    break;
            }

            sf::Text searchInput = createText(searchString, 24, sf::Color::White);
            searchInput.setFont(font);
            searchInput.setPosition(240, 25);

            // Draw elements and display window
            window.clear(Color(26, 42, 61, 0));
            window.draw(sideBar);
            window.draw(titleText1);
            window.draw(titleText2);

            for (int i = 0; i < buttons.size(); i++) {
                buttons.at(i).drawButton(window);
            }

            window.draw(searchBox);
            if (!textEntered) {
                window.draw(searchText);
            }
            else {
                window.draw(searchInput);
            }
            window.draw(gameBox);
            window.display();
        }
    }

    return 0;
};