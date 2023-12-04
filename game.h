#include <iostream>
#include <vector>
#pragma once
using namespace std;

class Game {
private:
    string title;
    string releaseDate;
    float price;
    int peakCCU;
    string desc;
    bool windows;
    bool mac;
    bool linux;
    float positive;
    float negative;
    float rating;
    int metacritic;
    int averagePlaytime;
    vector<string> genres;
public:
    Game();
    Game(string title, string releaseDate, float price, int peakCCU, int averagePlaytime);
    void addDesc(string description);
    void compatibleOS(bool windows, bool mac, bool linux);
    void setRating(int metacriticRating, float positive, float negative);
    void editGenres(vector<string> genres);
    int getPeakCCU();
    string getTitle();
    float getRatingValue();
    float getPrice();
    string getReleaseDate();
    int getMetacritic();
    float getPositive();
    int getPlaytime();
    bool getWindows();
    bool getMac();
    bool getLinux();
    vector<string> getGenres();
};

