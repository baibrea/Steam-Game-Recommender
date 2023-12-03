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
void Game::getRating(int metacriticRating, float positive, float negative) {
    this->metacritic = metacriticRating;
    float sumReviews = positive + negative;
    if (sumReviews != 0) {
        this->rating = positive / sumReviews;
    }
    else {
        this->rating = 0;
    }
}
void Game::editGenres(vector<string> genres) {
    this->genres = genres;
}

int Game::getPeakCCU() {
    return peakCCU;
}

string Game::getTitle() {
    return title;
}
