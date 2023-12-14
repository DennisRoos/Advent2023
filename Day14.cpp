#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;
char platform[102][102];
int sidelength;

string encode() {
	string s = "";
	for (int y = 1; y <= sidelength; y++) {
		for (int x = 1; x <= sidelength; x++) {
			s += platform[x][y];
		}
	}
	return s;
}

void RollNorth() {
	for (int y = 2; y <= sidelength; y++) {
		for (int x = 1; x <= sidelength; x++) {
			if (platform[x][y] == 'O') {
				int j = y - 1;
				while (platform[x][j] == '.') {
					j--;
				}
				platform[x][y] = '.';
				platform[x][j + 1] = 'O';
			}
		}
	}
}

void RollWest() {
	for (int x = 2; x <= sidelength; x++) {
		for (int y = 1; y <= sidelength; y++) {
			if (platform[x][y] == 'O') {
				int j = x - 1;
				while (platform[j][y] == '.') {
					j--;
				}
				platform[x][y] = '.';
				platform[j + 1][y] = 'O';
			}
		}
	}
}

void RollSouth() {
	for (int y = 99; y > 0; y--) {
		for (int x = 1; x <= sidelength; x++) {
			if (platform[x][y] == 'O') {
				int j = y + 1;
				while (platform[x][j] == '.') {
					j++;
				}
				platform[x][y] = '.';
				platform[x][j - 1] = 'O';
			}
		}
	}
}

void RollEast() {
	for (int x = 99; x > 0; x--) {
		for (int y = 1; y <= sidelength; y++) {
			if (platform[x][y] == 'O') {
				int j = x + 1;
				while (platform[j][y] == '.') {
					j++;
				}
				platform[x][y] = '.';
				platform[j - 1][y] = 'O';
			}
		}
	}
}


int load() {
	int total = 0;
	for (int x = 1; x <= sidelength; x++) {
		for (int y = 1; y <= sidelength; y++) {
			if (platform[x][y] == 'O')
				total += sidelength + 1 - y;
		}
	}
	return total;
}

void print() {
	for (int y = 1; y <= sidelength; y++) {
		for (int x = 1; x <= sidelength; x++) {
			cout << platform[x][y];
		}
		cout << endl;
	}
}


int main(int argc, char* argv[]) {
	int total1 = 0;
	int total2 = 0;
	sidelength = 100;
	for (int i = 0; i < sidelength + 2; i++) {//put boulders around edge
		platform[i][0] = '#';
		platform[i][sidelength + 1] = '#';
		platform[0][i] = '#';
		platform[sidelength + 1][i] = '#';
	}
	ifstream f("data.txt");
	string s;
	for (int y = 1; y <= sidelength; y++) {
		f >> s;
		for (int x = 0; x < sidelength; x++) {
			platform[x + 1][y] = s[x];
		}
	}
	RollNorth();
	total1 = load();
	RollWest();
	RollSouth();
	RollEast();
	int cycle = 1;
	bool b = true;
	vector<string> prevs;
	prevs.push_back("");//initialize 0;
	long long current;
	long long offset;
	while (b) {
		string s = encode();
		for (long long i = 1; i < prevs.size(); i++) {
			if (s.compare(prevs[i]) == 0) { //we've seen this pattern before
				offset = i;
				current = cycle;
				b = false;
			}
		}
		if (b) {
			prevs.push_back(s);
			cycle++;
			RollNorth();
			RollWest();
			RollSouth();
			RollEast();
		}
	}
	cout << current << "," << offset << endl;
	long long period = current - offset;//time the loop takes
	long long remaining = (1000000000 - current) % period;
	for (long long i = 0; i < remaining; i++) {
		RollNorth();
		RollWest();
		RollSouth();
		RollEast();
	}
	total2 = load();

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}