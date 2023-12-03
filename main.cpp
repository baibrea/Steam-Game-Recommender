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

    return 0;
};