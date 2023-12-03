#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

class number {//(x,y) is the coordinate of the leftmost part of the number
public:
	int x;
	int y;
	int value;
	int length; //number of digits
	int gearx;
	int geary;
	bool gear;

	number(int a, int b, int v, int l) {
		x = a;
		y = b;
		value = v;
		length = l;
		gear = false;
	}
};

int gearx;//Coordinates of the latest found gear
int geary;//I hate using globals for this, but feels like the easiest way
vector<number*> numberlist; //list of all numbers next to gears
char Schematic[142][142];

bool isSymbol(int x, int y) {
	char c = Schematic[x][y];
	if (c == '*') {//gear
		gearx = x;
		geary = y;
	}
	return (c != '.' && (c < '0' || c > '9'));
}

bool checkIfPart(number* N) {
	int x = N->x;
	int y = N->y;
	for (int i = 0; i < N->length; i++) {// can probably be done smarter 
		if (isSymbol(x - 1, y - 1) || isSymbol(x, y - 1) || isSymbol(x + 1, y - 1) ||
			isSymbol(x - 1, y) || isSymbol(x + 1, y) ||
			isSymbol(x - 1, y + 1) || isSymbol(x, y + 1) || isSymbol(x + 1, y + 1)) {
			if (gearx != -1) {//we found a gear next to this part
				N->gearx = gearx;
				N->geary = geary;
				N->gear = true;
			}
			return true;
		}
		x++;
	}
	return false;
}

int main(int argc, char* argv[]) {
	int total1 = 0;
	int total2 = 0;
	string s;
	for (int i = 0; i < 142; i++) {// initialize boundaries to avoid (literal) edge cases
		Schematic[0][i] = '.';
		Schematic[i][0] = '.';
		Schematic[141][i] = '.';
		Schematic[i][141] = '.';
	}
	ifstream f("data.txt");

	for (int y = 1; y <= 140; y++) {//initialize array
		f >> s;
		for (int x = 0; x < 140; x++) {
			Schematic[x + 1][y] = s[x];
		}
	}

	for (int y = 1; y <= 140; y++) {//find all numbers and check them
		for (int x = 1; x <= 140; x++) {
			if (Schematic[x][y] >= '0' && Schematic[x][y] <= '9') {//we found a number
				gearx = -1;
				int v = Schematic[x][y] - '0';
				int l = 1;
				while (Schematic[x+l][y] >= '0' && Schematic[x+l][y] <= '9') {
					v = (v * 10) + (Schematic[x+l][y] - '0');
					l++;
				}
				number* N = new number(x, y, v, l);
				if (checkIfPart(N)) {
					total1 += N->value;
					if (N->gear) {//this part was next to a gear, so we check if we've already found a matching part
						for (int i = 0; i < numberlist.size(); i++) {
							number* M = numberlist[i];
							if (N->gearx == M->gearx && N->geary == M->geary) 
								total2 += N->value * M->value;
						}
						numberlist.push_back(N);
					}
				}
				x += l;
			}
		}
	}
	
	cout << "The answer for part 1 is " << total1 << endl;
	cout << "The answer for part 2 is " << total2 << endl;
	return 0;
}