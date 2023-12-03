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
    int rating;
    int averagePlaytime;
    vector<string> genres;
public:
    Game(string title, string releaseDate, float price, int peakCCU, int averagePlaytime);
    void addDesc(string description);
    void compatibleOS(bool windows, bool mac, bool linux);
    void getRating(int metacriticRating, int positive, int negative);
    void editGenres(vector<string> genres);
};

