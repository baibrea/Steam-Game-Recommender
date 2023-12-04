#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include "extra.h"
#include "game.h"
#include "sfml.h"
#include "button.h"
#include <chrono>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main() {
    // Create containers (Game objects, filterButtons)
    map<string, Game> steamGames;
    vector<Game> foundGames;

    // Parse database and create new Game objects
    fstream file("games.csv", ios_base::in);
    //TODO: After container is created, pass container by reference into parseFile() so Game objects can be added to it
    parseFile(file, steamGames);

    // Extra array for sorting
//    cout << steamGames.size();
    vector<Game> arr;
    for(auto &game: steamGames) {
        arr.push_back(game.second);
    }

////     Running QuickSort
//    quickSort(arr, 0, arr.size()-1, "price");
//    for(int i = 0; i < arr.size(); i++) {
//        cout << "Game: " << arr.at(i).getTitle() << " Price: " << arr.at(i).getPrice() << endl;
//    }

////  Running MergeSort
//    mergeSort(arr, 0, arr.size()-1, "rating");
//    for(int i = 0; i < arr.size()-1; i++) {
//        cout << "Game: " << arr.at(i).getTitle() << " Rating: " << arr.at(i).getRatingValue() << endl;
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
    bool displayTitles = false;
    string searchString = "|";
    int startIndex = 0;

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

    titleText1.setOutlineThickness(3);
    titleText2.setOutlineThickness(3);
    titleText1.setOutlineColor(Color(24, 68, 84));
    titleText2.setOutlineColor(Color(24, 68, 84));

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
    filterText.setOutlineThickness(2);
    filterText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(filterText, 100, 150);
    texts.push_back(filterText);

    sf::Text priceText = createText("Price", 22, sf::Color::White);
    priceText.setFont(font);
    priceText.setOutlineThickness(2);
    priceText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(priceText, 96, 190);
    texts.push_back(priceText);

    sf::Text ratingText = createText("Rating", 22, sf::Color::White);
    ratingText.setFont(font);
    ratingText.setOutlineThickness(2);
    ratingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(ratingText, 104, 230);
    texts.push_back(ratingText);

    sf::Text popularityText = createText("Popularity", 22, sf::Color::White);
    popularityText.setFont(font);
    popularityText.setOutlineThickness(2);
    popularityText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(popularityText, 120, 270);
    texts.push_back(popularityText);

    sf::Text usingText = createText("Using:", 22, sf::Color::White);
    usingText.setFont(font);
    usingText.setStyle(sf::Text::Bold);
    usingText.setOutlineThickness(2);
    usingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(usingText, 100, 320);
    texts.push_back(usingText);

    sf::Text quickSortText = createText("Quick Sort", 22, sf::Color::White);
    quickSortText.setFont(font);
    quickSortText.setOutlineThickness(2);
    quickSortText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(quickSortText, 120, 360);
    texts.push_back(quickSortText);

    sf::Text mergeSortText = createText("Merge Sort", 22, sf::Color::White);
    mergeSortText.setFont(font);
    mergeSortText.setOutlineThickness(2);
    mergeSortText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(mergeSortText, 125, 400);
    texts.push_back(mergeSortText);

    sf::Text efficiencyText = createText("Efficiency:", 22, sf::Color::White);
    efficiencyText.setFont(font);
    efficiencyText.setOutlineThickness(2);
    efficiencyText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(efficiencyText, 70, 525);
    texts.push_back(efficiencyText);

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
    sortText.setOutlineColor(sf::Color(64, 64, 64));
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

        // Update "Sort" button visuals
        sortButton.setFillColor(sf::Color(160, 160, 160));
        sortText.setFillColor(sf::Color::White);

        // Handles User Interaction with Window
        char input;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // If user closes window, close
                case Event::Closed:
                    window.close();
                    break;

                // If user enters text, append characters to search box text
                case Event::TextEntered:
                    if (typing) {
                        input = static_cast<char>(event.text.unicode);
                        if (31 < event.text.unicode && event.text.unicode < 128) {
                            textEntered = true;
                            searchString.pop_back();
                            searchString.push_back(input);
                            searchString.push_back('|');
                        }
                    }
                    break;
                case Event::KeyPressed:
                    // If user presses backspace, delete the last character in the search bar
                    if (typing) {
                        if (event.key.code == sf::Keyboard::Backspace && searchString.size() > 1) {
                            searchString.pop_back();
                            searchString.pop_back();
                            searchString.push_back('|');
                        }
                        // If user presses enter, search for current string in game titles
                        if (event.key.code == sf::Keyboard::Enter && searchString.size() > 1) {
                            foundGames.clear();
                            startIndex = 0;
                            string title = searchString.substr(0, searchString.size() - 1);
                            for (auto& letter : title) {
                                if (isalpha(letter)) {
                                    letter = tolower(letter);
                                }
                            }

                            for (map<string, Game>::iterator itr = steamGames.begin(); itr != steamGames.end(); itr++) {
                                string currTitle = itr->first;
                                for (auto& letter : currTitle) {
                                    if (isalpha(letter)) {
                                        letter = tolower(letter);
                                    }
                                }
                                if (currTitle.find(title) != std::string::npos) {
                                    foundGames.push_back(itr->second);
                                }
                            }
                            cout << foundGames.size();
                        }
                    }

                    // Placeholder Text
                    break;
                case Event::MouseButtonPressed:
                    sf::Mouse mouse;
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = mouse.getPosition(window);
                        leftMouseClick(mousePosition.x, mousePosition.y, filterButtons);
                        leftMouseClick(mousePosition.x, mousePosition.y, algoButtons);
                        if (sortButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            sortButton.setFillColor(sf::Color(96, 96, 96));
                            sortText.setFillColor(sf::Color(192, 192, 192));

                            chrono::time_point<chrono::high_resolution_clock> startTime = chrono::high_resolution_clock::now();
                            // TODO: Sort by selected filters
                            // quickSort(arr, 0, arr.size()-1, "rating");
                            chrono::time_point<chrono::high_resolution_clock> endTime = chrono::high_resolution_clock::now();
                            chrono::duration<float> timePassed = endTime - startTime;
                            cout << "Sorting executed in " << timePassed.count() << " seconds.";
                        }
                        typing = clickedSearchBar(searchBox, mousePosition);
                        if (typing) {
                            textEntered = true;
                            if (searchString.at(searchString.size() - 1) != '|') {
                                searchString.push_back('|');
                            }
                        }
                        if (!typing) {
                            if (searchString.size() > 1 && searchString != "search") {
                                cout << searchString << endl;
                                if (searchString.at(searchString.size() - 1) == '|') {
                                    searchString.pop_back();
                                }
                            }
                            else {
                                textEntered = false;
                            }
                        }
                    }
                    break;
                case Event::MouseWheelScrolled:
                    cout << event.mouseWheelScroll.delta << endl;
                    if (event.mouseWheelScroll.delta > 0 && startIndex > 0) {
                        startIndex--;
                    }
                    else if (event.mouseWheelScroll.delta < 0) {
                        startIndex++;
                    }
                    break;
            }

            // Modify text in search bar
            sf::Text searchInput = createText(searchString, 24, sf::Color::White);
            searchInput.setFont(font);
            searchInput.setPosition(240, 25);

            // Create boxes to display game titles
            vector<sf::RectangleShape> titleBoxes;
            int height = 102;
            for (int i = 0; i < 14; i++) {
                sf::RectangleShape newBox = createTitleBox(height);
                titleBoxes.push_back(newBox);
                height += 35;
            }

            height = 90;
            vector<sf::Text> titleTexts;
            if (!foundGames.empty() && startIndex < foundGames.size()) {
                for (int j = startIndex; j < foundGames.size(); j++) {
                    sf::Text newText = createText(foundGames.at(j).getTitle(), 22, sf::Color::White);
                    newText.setFont(font);
                    newText.setPosition(230, height);
                    titleTexts.push_back(newText);
                    height += 35;
                }
            }

            // Draw elements and display window
            window.clear(Color(26, 42, 61, 0));
            window.draw(sideBar);

            for (auto& button : filterButtons) {
                button.drawButton(window);
            }
            for (auto& text : texts) {
                window.draw(text);
            }
            for (auto& button : algoButtons) {
                button.drawButton(window);
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
            for (auto& box : titleBoxes) {
                window.draw(box);
            }
            if (titleTexts.size() > 0) {
                if (titleTexts.size() >= 14) {
                    for (int i = 0; i < 14; i++) {
                        window.draw(titleTexts.at(i));
                    }
                }
                else {
                    for (auto &title: titleTexts) {
                        window.draw(title);
                    }
                }
            }

            window.display();
        }
    }

    return 0;
};