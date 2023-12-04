#include "extra.h"
#include <limits>
#include <regex>

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
            getline(stream, temp, ',');
            for (auto& letter : temp) {
                if (31 < static_cast<unsigned char>(letter) && static_cast<unsigned char>(letter) < 128) {
                    title.push_back(letter);
                }
            }

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
            newGame.setRating(metacritic, positive, negative);
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

void quickSort(vector<Game>& arr, int low, int high, string filter) {
    stack<int> stack;
    stack.push(low);
    stack.push(high);
    while(!stack.empty()) {
        high = stack.top();
        stack.pop();
        low = stack.top();
        stack.pop();

        int pivotPosition = partition(arr, low, high, filter);

        if(pivotPosition - 1 > low) {
            stack.push(low);
            stack.push(pivotPosition - 1);
        }

        if(pivotPosition + 1 < high) {
            stack.push(pivotPosition + 1);
            stack.push(high);
        }
    }
}

int partition(vector<Game>& arr, int low, int high, string filter) {
    int mid = (low + high) / 2;
    double pivotValue;
    if(filter == "price") {
        if(arr[mid].getPrice() < arr[low].getPrice() < arr[high].getPrice() || arr[high].getPrice() < arr[low].getPrice() < arr[mid].getPrice())
            pivotValue = arr[low].getPrice();
        else if(arr[low].getPrice() < arr[mid].getPrice() < arr[high].getPrice() || arr[high].getPrice() < arr[mid].getPrice() < arr[low].getPrice())
            pivotValue = arr[mid].getPrice();
        else
            pivotValue = arr[high].getPrice();
    }
    else if(filter == "rating") {
        if(arr[mid].getRatingValue() < arr[low].getRatingValue() < arr[high].getRatingValue() || arr[high].getRatingValue() < arr[low].getRatingValue() < arr[mid].getRatingValue())
            pivotValue = arr[low].getRatingValue();
        else if(arr[low].getRatingValue() < arr[mid].getRatingValue() < arr[high].getRatingValue() || arr[high].getRatingValue() < arr[mid].getRatingValue() < arr[low].getRatingValue())
            pivotValue = arr[mid].getRatingValue();
        else
            pivotValue = arr[high].getRatingValue();
    }
    else if(filter == "peakCCU") {
        if(arr[mid].getPeakCCU() < arr[low].getPeakCCU() < arr[high].getPeakCCU() || arr[high].getPeakCCU() < arr[low].getPeakCCU() < arr[mid].getPeakCCU())
            pivotValue = arr[low].getPeakCCU();
        else if(arr[low].getPeakCCU() < arr[mid].getPeakCCU() < arr[high].getPeakCCU() || arr[high].getPeakCCU() < arr[mid].getPeakCCU() < arr[low].getPeakCCU())
            pivotValue = arr[mid].getPeakCCU();
        else
            pivotValue = arr[high].getPeakCCU();
    }
    int up = low, down = high;

    while(up < down) {
        for(int j = up; j < high; j++) {
            if(quickUpHelper(arr[up], pivotValue, filter)) {
                break;
            }
            up++;
        }
        for(int j = high; j > low; j--) {
            if(quickDownHelper(arr[down], pivotValue, filter)) {
                break;
            }
            down--;
        }
        if(up < down) {
            swap(arr[up], arr[down]);
        }
    }
    swap(arr[low], arr[down]);
//    cout << "Still running: " << endl;
    return down;
}

bool quickUpHelper(Game& up, double pivotValue, string filter) {
    if(filter == "price") {
        return up.getPrice() > pivotValue;
    }
    else if(filter == "rating") {
        return up.getRatingValue() > pivotValue;
    }
    else if(filter == "peakCCU") {
        return (float)up.getPeakCCU() > pivotValue;
    }
}

bool quickDownHelper(Game& down, double pivotValue, string filter) {
    if(filter == "price") {
        return down.getPrice() < pivotValue;
    }
    else if(filter == "rating") {
        return down.getRatingValue() < pivotValue;
    }
    else if(filter == "peakCCU") {
        return (float)down.getPeakCCU() < pivotValue;
    }
}

void mergeSort(vector<Game>& arr, int left, int right, string filter) {
    if(left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid, filter);
        mergeSort(arr, mid + 1, right, filter);
        merge(arr, left, mid, right, filter);
    }
}

void merge(vector<Game>& arr, int left, int mid, int right, string filter) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    vector<Game> leftSection, rightSection;

    for(int i = 0; i < leftSize; i++) {
        leftSection.push_back(arr[left+i]);
    }
    for(int j = 0; j < rightSize; j++) {
        rightSection.push_back(arr[mid+1+j]);
    }

    int leftIndex = 0, rightIndex = 0;
    int mergedIndex = left;

    while(leftIndex < leftSize && rightIndex < rightSize) {
         if(mergeHelper(leftSection[leftIndex], rightSection[rightIndex], filter)) {
             arr[mergedIndex] = leftSection[leftIndex];
             leftIndex++;
         }
         else {
             arr[mergedIndex] = rightSection[rightIndex];
             rightIndex++;
         }
         mergedIndex++;
    }

    while(leftIndex < leftSize) {
        arr[mergedIndex] = leftSection[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    while(rightIndex < rightSize) {
        arr[mergedIndex] = rightSection[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
//    cout << "Still running..." << endl;
}

bool mergeHelper(Game leftGame, Game rightGame, string filter) {
    if(filter == "price") {
        return leftGame.getPrice() <= rightGame.getPrice();
    }
    else if(filter == "rating") {
        return leftGame.getRatingValue() <= rightGame.getRatingValue();
    }
    else if(filter == "peakCCU") {
        return leftGame.getPeakCCU() <= rightGame.getPeakCCU();
    }
}
