#include <iostream>
#include <vector>
#include <fstream>
#include "extra.h"
#include "game.h"
using namespace std;

int main() {
    //TODO: Create container for Game objects

    // Parse database and create new Game objects
    fstream file("games.csv", ios_base::in);
    //TODO: After container is created, pass container by reference into parseFile() so Game objects can be added to it
    parseFile(file);

    return 0;
};