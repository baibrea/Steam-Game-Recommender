#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <stack>
#include "game.h"
#pragma once
using namespace std;

void parseFile(fstream& file, map<string, Game>& games);

// TODO: Implement sorting algorithm methods


void quickSort(vector<Game>& arr, int low, int high, string filter);
int partition(vector<Game>& arr, int low, int high, string filter);
bool quickUpHelper(Game up, double pivotValue, string filter);
bool quickDownHelper(Game down, double pivotValue, string filter);

void mergeSort(vector<Game>& arr, int left, int right, string filter);
void merge(vector<Game>& arr, int left, int mid, int right, string filter);
bool mergeHelper(Game leftGame, Game rightGame, string filter);
