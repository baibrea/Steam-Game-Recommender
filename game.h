#include <iostream>
#include <vector>
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
    int metacritic;
    int positive;
    int negative;
    int averagePlaytime;
    vector<string> genres;
public:
    Game(string title);
    void editGenres(string genre);
};

