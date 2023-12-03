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
    // Create containers (Game objects, filterButtons)
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
//    quickSort(arr, 0, arr.size()-1, "peakCCU");
//    for(int i = 0; i < arr.size(); i++) {
//        cout << "Game: " << arr.at(i).getTitle() << " Peak CCU: " << arr.at(i).getPeakCCU() << endl;
//    }

    // Code for UI
    // Create window
    RenderWindow window(VideoMode(1000, 600), "Steam Game Recommender", sf::Style::Close);

    // Sets the font to Arial
    Font font;
    font.loadFromFile("../files/Arial.ttf");

    // Vector to hold all sf::Text objects
    vector<sf::Text> texts;

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
    texts.push_back(titleText1);
    texts.push_back(titleText2);

    // Sidebar text
    sf::Text filterText = createText("Sort by:", 22, sf::Color::White);
    filterText.setFont(font);
    filterText.setStyle(sf::Text::Bold);
    setTextCenter(filterText, 100, 150);
    texts.push_back(filterText);

    sf::Text priceText = createText("Price", 22, sf::Color::White);
    priceText.setFont(font);
    setTextCenter(priceText, 96, 190);
    texts.push_back(priceText);

    sf::Text ratingText = createText("Rating", 22, sf::Color::White);
    ratingText.setFont(font);
    setTextCenter(ratingText, 104, 230);
    texts.push_back(ratingText);

    sf::Text popularityText = createText("Popularity", 22, sf::Color::White);
    popularityText.setFont(font);
    setTextCenter(popularityText, 120, 270);
    texts.push_back(popularityText);

    sf::Text usingText = createText("Using:", 22, sf::Color::White);
    usingText.setFont(font);
    usingText.setStyle(sf::Text::Bold);
    setTextCenter(usingText, 100, 320);
    texts.push_back(usingText);

    sf::Text quickSortText = createText("Quick Sort", 22, sf::Color::White);
    quickSortText.setFont(font);
    setTextCenter(quickSortText, 120, 360);
    texts.push_back(quickSortText);

    sf::Text mergeSortText = createText("Merge Sort", 22, sf::Color::White);
    mergeSortText.setFont(font);
    setTextCenter(mergeSortText, 125, 400);
    texts.push_back(mergeSortText);

    // Create filterButtons
    vector<Button> filterButtons{};
    Button priceButton("price", 50, 190);
    filterButtons.push_back(priceButton);
    Button ratingButton("rating", 50, 230);
    filterButtons.push_back(ratingButton);
    Button peakCCUButton("peakCCU", 50, 270);
    filterButtons.push_back(peakCCUButton);

    vector<Button> algoButtons{};
    Button quickSortButton("quickSort", 50, 360);
    algoButtons.push_back(quickSortButton);
    Button mergeSortButton("mergeSort", 50, 400);
    algoButtons.push_back(mergeSortButton);

    // Create "Sort" button
    sf::RectangleShape sortButton(sf::Vector2f(80, 40));
    sortButton.setFillColor(sf::Color(160, 160, 160));
    sortButton.setOutlineThickness(4);
    sortButton.setOutlineColor(sf::Color(64, 64, 64));
    sf::FloatRect rectBounds = sortButton.getLocalBounds();
    sortButton.setOrigin(rectBounds.left + rectBounds.width/2.0f, rectBounds.top + rectBounds.height/2.0f);
    sortButton.setPosition(100, 460);

    sf::Text sortText = createText("SORT", 22, sf::Color::White);
    sortText.setOutlineThickness(1.5);
    sortText.setOutlineColor(sf::Color::Black);
    sortText.setFont(font);
    sortText.setStyle(sf::Text::Bold);
    setTextCenter(sortText, 100, 460);

    // Textbox for game search
    sf::RectangleShape searchBox(sf::Vector2f(750, 40));
    searchBox.setFillColor(sf::Color(37, 78, 110));
    rectBounds = searchBox.getLocalBounds();
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
                        leftMouseClick(x, y, filterButtons);
                        leftMouseClick(x, y, algoButtons);

                        if (searchBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            typing = true;
                            if (searchString == "|")
                                textEntered = true;
                        }
                        if (sortButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            // TODO: Sort by selected filters
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

            for (int i = 0; i < filterButtons.size(); i++) {
                filterButtons.at(i).drawButton(window);
            }

            for (int j = 0; j < texts.size(); j++) {
                window.draw(texts.at(j));
            }

            for (int k = 0; k < algoButtons.size(); k++) {
                algoButtons.at(k).drawButton(window);
            }
            window.draw(sortButton);
            window.draw(sortText);
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