#include "game.h"

Game::Game(string title) {
    this->title = title;
}

//TODO: Find a way to update object's variables

void Game::editGenres(string genre) {
    genres.push_back(genre);
}
