#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

#include <algorithm> 

using namespace std;

bool Map[150][150];
vector<long long> X1;
vector<long long> Y1;
vector<long long> X2;
vector<long long> Y2;

int main(int argc, char* argv[]) {
	long long total1 = 0;
	long long total2 = 0;
	int x;
	int y = 0;
	ifstream f("data.txt");
	string s;
	while (f >> s) {
		for (x = 0; x < s.size(); x++) {
			bool b = (s[x] == '#');
			Map[x][y] = b;
			if (b) {
				X1.push_back(x);
				Y1.push_back(y);
				X2.push_back(x);
				Y2.push_back(y);
			}
		}
		y++;
	}
	for (int i = y - 1; i >= 0; i--) { // double all empty rows by incrementing the Y value for all galaxies below that row
		bool notEmpty = false;
		for (int j = 0; j < x; j++) {
			notEmpty = notEmpty || Map[j][i];
		}
		if (!notEmpty) {
			for (int k = 0; k < X1.size(); k++) {
				if (i < Y1[k]) {
					Y1[k]++;
					Y2[k] += 999999;
				}
			}
		}
	}
	for (int i = x - 1; i >= 0; i--) { // do the same for columns
		bool notEmpty = false;
		for (int j = 0; j < y; j++) {
			notEmpty = notEmpty || Map[i][j];
		}
		if (!notEmpty) {
			for (int k = 0; k < X1.size(); k++) {
				if (i < X1[k]) {
					X1[k]++;
					X2[k] += 999999;
				}
			}
		}
	}
	for (int i = 0; i < X1.size(); i++) { // calculate manhattan distance
		for (int j = 0; j < i; j++) {
			total1 += abs(X1[i] - X1[j]) + abs(Y1[i] - Y1[j]);
			total2 += abs(X2[i] - X2[j]) + abs(Y2[i] - Y2[j]);
		}
	}
	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}