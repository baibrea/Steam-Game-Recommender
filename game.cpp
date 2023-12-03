#include "game.h"

Game::Game(string title, string releaseDate, float price, int peakCCU, int averagePlaytime) {
    this->title = title;
    this->releaseDate = releaseDate;
    this->price = price;
    this->peakCCU = peakCCU;
    this->averagePlaytime = averagePlaytime;
}

void Game::addDesc(string description) {
    this->desc = description;
}

void Game::compatibleOS(bool windows, bool mac, bool linux) {
    this->windows = windows;
    this->mac = mac;
    this->linux = linux;
}
void Game::getRating(int metacriticRating, int positive, int negative) {
    this->metacritic = metacriticRating;
    int sumReviews = positive + negative;
    this->rating = positive / negative;
    cout << rating << endl;
}
void Game::editGenres(vector<string> genres) {
    this->genres = genres;
}
