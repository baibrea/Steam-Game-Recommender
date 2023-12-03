#include "extra.h"
#include <limits>

void parseFile(fstream& file) {
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
        int peakCCU, metacritic, positive, negative, averagePlaytime;
        float price;
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
            positive = stoi(temp);
            getline(stream, temp, ',');
            negative = stoi(temp);
            getline(stream, temp, ',');
            averagePlaytime = stoi(temp);
            //FIXME: This is for testing--delete when done
            count++;
            cout << title << " " << count << endl;
        }
        catch(exception &err) {
            stream.ignore(numeric_limits<streamsize>::max());
            continue;
        }
    }

}