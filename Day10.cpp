#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

#include <algorithm> 

using namespace std;


char Map[140][140];
int A[140][140];
int xlength;
int ylength;
vector<int> X;
vector<int> Y;

void append(int x, int y) {
	if (x >= 0 && y >= 0 && x < 140 && y < 140 && A[x][y] == 0) {
		X.push_back(x);
		Y.push_back(y);
	}
}

int navigate(int x, int y, int direction) {
	int depth = 0;
	while (true) {
		A[x][y] = 1;
		//cout << x << "," << y << " " << Map[x][y] << endl;
		if (direction == 0)  //east
			x++;
		else if (direction == 1) //south
			y++;
		else if (direction == 2) //west
			x--;
		else //north
			y--;
		depth++;
		char c = Map[x][y];
		if (c == 'S')
			return depth;


		if (direction == 0) { //east
			if (c == 'J') {
				direction = 3;
				append(x, y + 1);
				append(x + 1, y);
			}
			else if (c == '7') {
				direction = 1;
			}
			else {
				append(x, y + 1);
			}
		}
		else if (direction == 1) { //south
			if (c == 'J') {
				direction = 2;
			}
			else if (c == 'L') {
				direction = 0;
				append(x, y + 1);
				append(x - 1, y);
			}
			else {
				append(x - 1, y);
			}
		}
		else if (direction == 2) { //west
			if (c == 'L') {
				direction = 3;
			}
			else if (c == 'F') {
				direction = 1;
				append(x, y - 1);
				append(x - 1, y);
			}
			else {
				append(x, y - 1);
			}
		}
		else { //north
			if (c == 'F') {
				direction = 0;
			}
			else if (c == '7') {
				direction = 2;
				append(x, y - 1);
				append(x + 1, y);
			}
			else {
				append(x + 1, y);
			}
		}
	}
}

int InsideTiles;

void paintInside(int x, int y) {
	if (A[x][y] == 0) {
		A[x][y] = 2;
		InsideTiles++;
		append(x + 1, y);
		append(x - 1, y);
		append(x, y + 1);
		append(x, y - 1);
	}
	return;
}

int main(int argc, char* argv[]) {
	int Sx;
	int Sy;
	xlength = 140;
	ylength = 140;
	ifstream f("data.txt");
	for (int y = 0; y < ylength; y++) {
		string s;
		f >> s;
		for (int x = 0; x < xlength; x++) {
			A[x][y] = 0;
			Map[x][y] = s[x];
			if (s[x] == 'S') {
				Sx = x;
				Sy = y;
			}
		}
	}
	int looplength = navigate(Sx, Sy,1);
	cout << "The answer to part 1 is " << looplength / 2 << endl;
	InsideTiles = 0;
	for (int i = 0; i < X.size(); i++) {
		paintInside(X[i], Y[i]);
	}
	cout << "The answer to part 2 is " << InsideTiles << endl;
	return 0;
}
