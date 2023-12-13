#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

char Map[50][50];
int x;
int y;

bool vertical(int left, int faults) {
	int right = left + 1;
	int count = 0;
	while (left >= 0 && right < x) {
		for (int i = 0; i < y; i++) {
			if (Map[left][i] != Map[right][i])//not a correct mirror
				count++;
		}
		left--;
		right++;
	}
	return (count == faults);
}


bool horizontal(int up, int faults) {
	int down = up + 1;
	int count = 0;
	while (up >= 0 && down < y) {
		for (int i = 0; i < x; i++) {
			if (Map[i][up] != Map[i][down])//not a correct reflection
				count++;
		}
		up--;
		down++;
	}
	return (count == faults);
}


int main(int argc, char* argv[]) {
	int total1 = 0;
	int total2 = 0;
	ifstream f("data.txt");
	string s;
	while (getline(f, s)) {
		y = 0;
		while (!s.empty()) {
			x = s.size();
			for (int i = 0; i < x; i++) {
				Map[i][y] = s[i];
			}
			y++;
			getline(f, s);
		}
		for (int i = 0; i < x - 1; i++) {
			if (vertical(i, 0))
				total1 += i + 1;
			if (vertical(i, 1))
				total2 += i + 1;
		}
		for (int i = 0; i < y - 1; i++) {
			if (horizontal(i, 0))
				total1 += ((i + 1) * 100);
			if (horizontal(i, 1))
				total2 += ((i + 1) * 100);
		}

	}
	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}