#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
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
    vector<Game> allGames;
    for(auto &game: steamGames) {
        allGames.push_back(game.second);
    }

////     Running QuickSort
//    quickSort(allGames, 0, allGames.size()-1, "price");
//    for(int i = 0; i < allGames.size(); i++) {
//        cout << "Game: " << allGames.at(i).getTitle() << " Price: " << allGames.at(i).getPrice() << endl;
//    }

////  Running MergeSort
//    mergeSort(allGames, 0, allGames.size()-1, "rating");
//    for(int i = 0; i < allGames.size()-1; i++) {
//        cout << "Game: " << allGames.at(i).getTitle() << " Rating: " << allGames.at(i).getRatingValue() << endl;
//    }


    // Code for UI
    // Create window
    RenderWindow window(VideoMode(1000, 600), "Steam Game Recommender", sf::Style::Close);

    // Sets the font to Arial
    Font font;
    font.loadFromFile("../files/Arial.ttf");

    // Vector to hold all sf::Text objects
    vector<sf::Text> texts;

    Event event;

    // Sets up back button
    Texture backButtonTexture;
    Sprite backButtonSprite;

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
    setTextCenter(filterText, 100, 120);
    texts.push_back(filterText);

    sf::Text priceText = createText("Price", 22, sf::Color::White);
    priceText.setFont(font);
    priceText.setOutlineThickness(2);
    priceText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(priceText, 96, 150);
    texts.push_back(priceText);

    sf::Text ratingText = createText("Rating", 22, sf::Color::White);
    ratingText.setFont(font);
    ratingText.setOutlineThickness(2);
    ratingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(ratingText, 104, 180);
    texts.push_back(ratingText);

    sf::Text popularityText = createText("Popularity", 22, sf::Color::White);
    popularityText.setFont(font);
    popularityText.setOutlineThickness(2);
    popularityText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(popularityText, 120, 210);
    texts.push_back(popularityText);

    sf::Text usingText = createText("Using:", 22, sf::Color::White);
    usingText.setFont(font);
    usingText.setStyle(sf::Text::Bold);
    usingText.setOutlineThickness(2);
    usingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(usingText, 100, 250);
    texts.push_back(usingText);

    sf::Text quickSortText = createText("Quick Sort", 22, sf::Color::White);
    quickSortText.setFont(font);
    quickSortText.setOutlineThickness(2);
    quickSortText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(quickSortText, 120, 280);
    texts.push_back(quickSortText);

    sf::Text mergeSortText = createText("Merge Sort", 22, sf::Color::White);
    mergeSortText.setFont(font);
    mergeSortText.setOutlineThickness(2);
    mergeSortText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(mergeSortText, 125, 310);
    texts.push_back(mergeSortText);

    sf::Text ascendingDescendingText = createText("Ascending/\nDescending:", 22, sf::Color::White);
    ascendingDescendingText.setFont(font);
    ascendingDescendingText.setStyle(sf::Text::Bold);
    ascendingDescendingText.setOutlineThickness(2);
    ascendingDescendingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(ascendingDescendingText, 100, 365);
    texts.push_back(ascendingDescendingText);

    sf::Text ascendingText = createText("Ascending", 22, sf::Color::White);
    ascendingText.setFont(font);
    ascendingText.setOutlineThickness(2);
    ascendingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(ascendingText, 125, 415);
    texts.push_back(ascendingText);

    sf::Text descendingText = createText("Descending", 22, sf::Color::White);
    descendingText.setFont(font);
    descendingText.setOutlineThickness(2);
    descendingText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(descendingText, 130, 445);
    texts.push_back(descendingText);

    sf::Text efficiencyText = createText("Efficiency:", 22, sf::Color::White);
    efficiencyText.setFont(font);
    efficiencyText.setOutlineThickness(2);
    efficiencyText.setOutlineColor(Color(24, 68, 84));
    setTextCenter(efficiencyText, 70, 545);
    texts.push_back(efficiencyText);

    // Create filterButtons
    vector<Button> filterButtons{};
    Button priceButton("price", 50, 150);
    filterButtons.push_back(priceButton);
    Button ratingButton("rating", 50, 180);
    filterButtons.push_back(ratingButton);
    Button peakCCUButton("peakCCU", 50, 210);
    filterButtons.push_back(peakCCUButton);

    vector<Button> algoButtons{};
    Button quickSortButton("quickSort", 50, 280);
    algoButtons.push_back(quickSortButton);
    Button mergeSortButton("mergeSort", 50, 310);
    algoButtons.push_back(mergeSortButton);

    vector<Button> ascendingDescendingButtons{};
    Button ascendingButton("ascending", 50, 415);
    ascendingDescendingButtons.push_back(ascendingButton);
    Button descendingButton("descending", 50, 445);
    ascendingDescendingButtons.push_back(descendingButton);

    // Create "Sort" button
    sf::RectangleShape sortButton(sf::Vector2f(80, 40));
    sortButton.setFillColor(sf::Color(160, 160, 160));
    sortButton.setOutlineThickness(4);
    sortButton.setOutlineColor(sf::Color(64, 64, 64));
    sf::FloatRect rectBounds = sortButton.getLocalBounds();
    sortButton.setOrigin(rectBounds.left + rectBounds.width/2.0f, rectBounds.top + rectBounds.height/2.0f);
    sortButton.setPosition(100, 495);

    sf::Text sortText = createText("SORT", 22, sf::Color::White);
    sortText.setOutlineThickness(1.5);
    sortText.setOutlineColor(sf::Color(64, 64, 64));
    sortText.setFont(font);
    sortText.setStyle(sf::Text::Bold);
    setTextCenter(sortText, 100, 495);

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

    // Create boxes to display game titles
    vector<sf::RectangleShape> titleBoxes;
    int height = 102;
    for (int i = 0; i < 14; i++) {
        sf::RectangleShape newBox = createTitleBox(height);
        titleBoxes.push_back(newBox);
        height += 35;
    }

    bool typing = false;
    bool textEntered = false;
    bool displayTitles = false;
    bool sorted = false;
    bool gameOpen = false;
    string searchString = "|";
    int startIndex = 0;
    string ascDesc = "ascending";

    Game currGame;

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
                        // If user presses "Enter," search for current string in game titles
                        if (event.key.code == sf::Keyboard::Enter) {
                            foundGames.clear();
                            startIndex = 0;
                            sorted = false;
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
                    break;
                case Event::MouseButtonPressed:
                    sf::Mouse mouse;
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = mouse.getPosition(window);
                        leftMouseClickButton(mousePosition.x, mousePosition.y, filterButtons);
                        leftMouseClickButton(mousePosition.x, mousePosition.y, algoButtons);
                        leftMouseClickButton(mousePosition.x, mousePosition.y, ascendingDescendingButtons);
                        if (!foundGames.empty() && !gameOpen) {
                            int titleNum;
                            titleNum = leftMouseClickTitle(mousePosition.x, mousePosition.y, titleBoxes);
                            if (foundGames.size() > (startIndex + titleNum)) {
                                gameOpen = true;
                                currGame = foundGames.at(startIndex + titleNum);
                                cout << currGame.getTitle() << endl;
                            }
                        }

                        if (sortButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            sortButton.setFillColor(sf::Color(96, 96, 96));
                            sortText.setFillColor(sf::Color(192, 192, 192));
//                            foundGames.clear();
                            startIndex = 0;

                            string filter;
                            for (auto& button : filterButtons) {
                                if (button.isActive()) {
                                    filter = button.getName();
                                }
                            }
                            string algorithm;
                            for (auto& button: algoButtons) {
                                if (button.isActive()) {
                                    algorithm = button.getName();
                                }
                            }
                            for (auto& button: ascendingDescendingButtons) {
                                if (button.isActive()) {
                                    ascDesc = button.getName();
                                }
                            }

                            chrono::time_point<chrono::high_resolution_clock> startTime = chrono::high_resolution_clock::now();

                            sorted = true;
                            // TODO: Sort by selected filters
                            if(foundGames.size() < 1) {
                                foundGames = allGames;
                            }
                            if (algorithm == "mergeSort") {
                                mergeSort(foundGames, 0, foundGames.size() - 1, filter);
                            }
                            else {
                                quickSort(foundGames, 0, foundGames.size() - 1, filter);
                            }
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
//                                cout << searchString << endl;
                                if (searchString.at(searchString.size() - 1) == '|') {
                                    searchString.pop_back();
                                }
                            }
                            else {
                                textEntered = false;
                            }
                        }

                        if (gameOpen && backButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            gameOpen = false;
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

            // Create text for game titles (search bar)
            // FIXME: Errors with printing out the sorted titles
            height = 90;
            vector<sf::Text> titleTexts;
            if (!foundGames.empty() && startIndex < foundGames.size()) {
                if(ascDesc == "ascending") {
                    for (int j = startIndex; j < foundGames.size(); j++) {
                        sf::Text newText = createText(foundGames.at(j).getTitle(), 22, sf::Color::White);
                        newText.setFont(font);
                        newText.setPosition(230, height);
                        titleTexts.push_back(newText);
                        height += 35;
                    }
                }
                else {
                    for (int j = foundGames.size() - 1; j >= startIndex; j--) {
                        sf::Text newText = createText(foundGames.at(j).getTitle(), 22, sf::Color::White);
                        newText.setFont(font);
                        newText.setPosition(230, height);
                        titleTexts.push_back(newText);
                        height += 35;
                    }
                }
            }

            // Create text for game titles (sorting algorithms)
            height = 90;
            if (sorted) {
                titleTexts.clear();
                if(ascDesc == "ascending") {
                    for (int k = startIndex; k < foundGames.size(); k++) {
                        sf::Text newText = createText(foundGames.at(k).getTitle(), 22, sf::Color::White);
                        newText.setFont(font);
                        newText.setPosition(230, height);
                        titleTexts.push_back(newText);
                        height += 35;
                    }
                }
                else {
                    for (int k = foundGames.size() - 1; k >= startIndex; k--) {
                        sf::Text newText = createText(foundGames.at(k).getTitle(), 22, sf::Color::White);
                        newText.setFont(font);
                        newText.setPosition(230, height);
                        titleTexts.push_back(newText);
                        height += 35;
                    }
                }
            }

            // Draw elements and display window
            window.clear(Color(26, 42, 61, 0));
            window.draw(sideBar);

            // Draw sidebar buttons and text
            for (auto& button : filterButtons) {
                button.drawButton(window);
            }
            for (auto& text : texts) {
                window.draw(text);
            }
            for (auto& button : algoButtons) {
                button.drawButton(window);
            }
            for (auto& button : ascendingDescendingButtons) {
                button.drawButton(window);
            }
            window.draw(sortButton);
            window.draw(sortText);

            // Draw search bar elements
            window.draw(searchBox);
            if (!textEntered) {
                window.draw(searchText);
            }
            else {
                window.draw(searchInput);
            }

            // Draw game window elements
            // Draw boxes if no game is currently open
            window.draw(gameBox);
            if (!gameOpen) {
                for (auto &box: titleBoxes) {
                    window.draw(box);
                }
            }
            // Draw game titles if no game is no game is currently open
            if (titleTexts.size() > 0 && !gameOpen) {
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

            // If game is open, create elements of the game's stats
            // TODO: Work on selected game's display
            if (gameOpen) {
                // Create title element
                string title = currGame.getTitle();
                sf::Text titleText = createText(title, 24, sf::Color::White);
                titleText.setFont(font);
                setTextCenter(titleText, 600, 110);

                backButtonTexture.loadFromFile("../files/images/backbutton.png");
                backButtonSprite.setTexture(backButtonTexture);
                // FIXME: Maybe tweak the position.
                backButtonSprite.setPosition(220, 80);
                window.draw(backButtonSprite);

                // Create labels for stats
                sf::Text releaseDateLabel = createText("RELEASE DATE:", 18, sf::Color(121, 136, 161));
                releaseDateLabel.setPosition(250, 140);
                releaseDateLabel.setFont(font);

                sf::Text priceLabel = createText("PRICE:", 18, sf::Color(121, 136, 161));
                priceLabel.setPosition(250, 170);
                priceLabel.setFont(font);

                sf::Text ratingLabel = createText("USER RATING:", 18, sf::Color(121, 136, 161));
                ratingLabel.setPosition(250, 200);
                ratingLabel.setFont(font);

                sf::Text metacriticLabel = createText("METACRITIC RATING:", 18, sf::Color(121, 136, 161));
                metacriticLabel.setPosition(250, 230);
                metacriticLabel.setFont(font);

                sf::Text osLabel = createText("AVAILABLE ON:", 18, sf::Color(121, 136, 161));
                osLabel.setPosition(250, 260);
                osLabel.setFont(font);

                sf::Text playtimeLabel = createText("AVERAGE PLAYTIME:", 18, sf::Color(121, 136, 161));
                playtimeLabel.setPosition(250, 290);
                playtimeLabel.setFont(font);

                sf::Text genresLabel = createText("TAGS:", 18, sf::Color(121, 136, 161));
                genresLabel.setPosition(250, 320);
                genresLabel.setFont(font);

                sf::Text descriptionLabel = createText("ABOUT:", 18, sf::Color(121, 136, 161));
                descriptionLabel.setPosition(250, 380);
                descriptionLabel.setFont(font);


                // Create stats text
                sf::Text releaseDate = createText(currGame.getReleaseDate(), 20, sf::Color(53, 155, 233));
                releaseDate.setStyle(sf::Text::Bold);
                releaseDate.setPosition(395, 138);
                releaseDate.setFont(font);

                string priceVal = "$" + to_string(floor(currGame.getPrice()));
                sf::Text price = createText(priceVal, 20, sf::Color(53, 155, 233));
                price.setStyle(sf::Text::Bold);
                price.setPosition(315, 168);
                price.setFont(font);

                float ratingVal = currGame.getRatingValue() * 100;
                sf::Text rating = createText(to_string(floor(ratingVal)) , 20, sf::Color(53, 155, 233));
                rating.setStyle(sf::Text::Bold);
                rating.setPosition(380, 198);
                rating.setFont(font);

                sf::Text metacriticRating = createText(to_string(floor(currGame.getMetacritic())) , 20, sf::Color(53, 155, 233));
                metacriticRating.setStyle(sf::Text::Bold);
                metacriticRating.setPosition(440, 228);
                metacriticRating.setFont(font);

                string availableSystems = "";
                int count = 0;
                if (currGame.getWindows()) {
                    availableSystems += "Windows";
                    count++;
                }
                if (currGame.getMac()) {
                    if (count > 0) {
                        availableSystems += ", ";
                    }
                    availableSystems += "Mac";
                    count++;
                }
                if (currGame.getLinux()) {
                    if (count > 0) {
                        availableSystems += ", ";
                    }
                    availableSystems += "Linux";
                }

                sf::Text os = createText(availableSystems, 20, sf::Color(53, 155, 233));
                os.setStyle(sf::Text::Bold);
                os.setPosition(390, 258);
                os.setFont(font);

                string playtimeVal = to_string(currGame.getPlaytime()) + " mins";
                sf::Text playtime = createText(playtimeVal, 20, sf::Color(53, 155, 233));
                playtime.setStyle(sf::Text::Bold);
                playtime.setPosition(435, 288);
                playtime.setFont(font);

                // Draw elements
                window.draw(titleText);
                window.draw(releaseDateLabel);
                window.draw(priceLabel);
                window.draw(ratingLabel);
                window.draw(metacriticLabel);
                window.draw(osLabel);
                window.draw(playtimeLabel);
                window.draw(descriptionLabel);
                window.draw(genresLabel);

                window.draw(releaseDate);
                window.draw(price);
                window.draw(rating);
                window.draw(metacriticRating);
                window.draw(os);
                window.draw(playtime);

            }



            window.display();
        }
    }

    return 0;
};