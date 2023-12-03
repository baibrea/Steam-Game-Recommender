#include "extra.h"
#include <limits>

void parseFile(fstream& file, map<string, Game>& steamGames) {
    // Bypass line that contains column titles
    string line;
    getline(file, line);
    int count = 0;

    // Parse CSV file into each games' stats
    // If line causes an error, skip
    while (!file.eof()) {
        getline(file, line);
        istringstream stream(line);
        string temp;

        string title, releaseDate, desc;
        int peakCCU, metacritic, averagePlaytime;
        float price, positive, negative;
        bool windows, mac, linux = false;

        try {
            getline(stream, title, ',');
            getline(stream, releaseDate, ',');
            getline(stream, temp, ',');
            peakCCU = stoi(temp);
            getline(stream, temp, ',');
            price = stof(temp);
            getline(stream, desc, '"');
            getline(stream, desc, '"');

            getline(stream, temp, ',');
            getline(stream, temp, ',');
            if (temp == "TRUE") {
                windows = true;
            }
            getline(stream, temp, ',');
            if (temp == "TRUE") {
                mac = true;
            }
            getline(stream, temp, ',');
            if (temp == "TRUE") {
                linux = true;
            }
            getline(stream, temp, ',');
            metacritic = stoi(temp);
            getline(stream, temp, ',');
            positive = stof(temp);
            getline(stream, temp, ',');
            negative = stof(temp);
            getline(stream, temp, ',');
            averagePlaytime = stoi(temp);

            // Create vector of the game's genres
            string genres;
            vector<string> genreList;
            getline(stream, genres);

            // FIXME: For testing
            //cout << genres << endl;

            // Delete quotation marks at beginning and end of string
            genres.erase(0, 1);
            genres.erase(genres.size() - 1, 1);
            while (genres.find(',') != string::npos) {
                int commaIndex = genres.find(',');
                string newGenre = genres.substr(0, commaIndex);
                genres.erase(0, newGenre.length() + 1);
                genreList.push_back(newGenre);
            }
            genreList.push_back(genres);

            // FIXME: This is for testing; delete when done
            count++;
            //cout << title << " " << count << endl;

            // Create a new Game object with the given stats
            Game newGame(title, releaseDate, price, peakCCU, averagePlaytime);
            newGame.addDesc(desc);
            newGame.compatibleOS(windows, mac, linux);
            newGame.getRating(metacritic, positive, negative);
            newGame.editGenres(genreList);

            // Add the new game to the container of Steam games
            steamGames.insert({title, newGame});
        }
        catch(exception &err) {
            stream.ignore(numeric_limits<streamsize>::max());
            continue;
        }
    }
}

void quickSort(vector<Game> arr, int low, int high, string filter) {
    if(low < high) {
        int pivotPosition = partition(arr, low, high, filter);
        quickSort(arr, low, pivotPosition - 1, filter);
        quickSort(arr, pivotPosition + 1, high, filter);
    }
}

int partition(vector<Game> arr, int low, int high, string filter) {
    int pivotValue = 0;
    if(filter == "peakCCU") {
        int firstValue = (low + rand() % (high - low));
        int secondValue = (low + rand() % (high - low));
        int thirdValue = (low + rand() % (high - low));
        if(thirdValue < firstValue < secondValue || secondValue < firstValue < thirdValue) {
            arr[firstValue].getPeakCCU();
        }
        else if (thirdValue < secondValue < firstValue || firstValue < secondValue << thirdValue) {
            arr[secondValue].getPeakCCU();
        }
        else {
            arr[thirdValue].getPeakCCU();
        }
    }
    int up = low, down = high;

    while(up < down) {
        for(int j = up; j < high; j++) {
            if(arr[up].getPeakCCU() > pivotValue) {
                break;
            }
            up++;
        }
        for(int j = high; j > low; j--) {
            if(arr[down].getPeakCCU() < pivotValue) {
                break;
            }
            down--;
        }
        if(up < down) {
            swap(arr[up], arr[down]);
        }
    }
    swap(arr[low], arr[down]);
    cout << "Still running: " << endl;
    return down;

}
