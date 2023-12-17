#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

int Map[141][141];
int Dist[141][141][4][10];
int sidelength;
int minlength;
int maxlength;

struct params {
	int x;
	int y;
	int l;
	int d;
};

vector<params> v;

void addToHeap(int x, int y, int l, int d) {
	params p = params();
	p.x = x;
	p.y = y;
	p.l = l;
	p.d = d;
	v.push_back(p);
}

void navigateEast(int x, int y, int length);
void navigateNorth(int x, int y, int length);
void navigateWest(int x, int y, int length);
void navigateSouth(int x, int y, int length);

void navigateEast(int x, int y, int length) {
	for(int i = 0; i < minlength; i++)
		length += Map[x - i][y];
	for (int depth = minlength - 1; depth < maxlength; depth++) {
		if (x >= sidelength || Dist[x][y][0][depth] <= length)
			return;
		Dist[x][y][0][depth] = length;
		addToHeap(x, y - minlength, length, 1);
		addToHeap(x, y + minlength, length, 3);
		x++;
		length += Map[x][y];
	}
}

void navigateNorth(int x, int y, int length) {
	for (int i = 0; i < minlength; i++)
		length += Map[x][y + i];
	for (int depth = minlength - 1; depth < maxlength; depth++) {
		if (y < 0 || Dist[x][y][1][depth] <= length)
			return;
		Dist[x][y][1][depth] = length;
		addToHeap(x - minlength, y, length, 2);
		addToHeap(x + minlength, y, length, 0);
		y--;
		length += Map[x][y];
	}
}

void navigateWest(int x, int y, int length) {
	for (int i = 0; i < minlength; i++)
		length += Map[x + i][y];
	for (int depth = minlength - 1; depth < maxlength; depth++) {
		if (x < 0 || Dist[x][y][2][depth] <= length)
			return;
		Dist[x][y][2][depth] = length;
		addToHeap(x, y - minlength, length, 1);
		addToHeap(x, y + minlength, length, 3);
		x--;
		length += Map[x][y];
	}
}

void navigateSouth(int x, int y, int length) {
	for (int i = 0; i < minlength; i++)
		length += Map[x][y - i];
	for (int depth = minlength - 1; depth < maxlength; depth++) {
		if (y >= sidelength || Dist[x][y][3][depth] <= length)
			return;
		Dist[x][y][3][depth] = length;
		addToHeap(x - minlength, y, length, 2);
		addToHeap(x + minlength, y, length, 0);
		y++;
		length += Map[x][y];
	}
}

int main(int argc, char* argv[]) {
	int total1 = 9999999;
	int total2 = 9999999;
	sidelength = 141;
	minlength = 1;
	maxlength = 3;
	ifstream f("data.txt");
	string s;
	for (int y = 0; y < sidelength; y++) {
		f >> s;
		for (int x = 0; x < sidelength; x++) {
			Map[x][y] = s[x] - '0';
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 10; j++) {
					Dist[x][y][i][j] = 9999999;
				}
			}
		}
	}
	addToHeap(0, 0, -Map[0][0], 0);
	addToHeap(0, 0, -Map[0][0], 3);

	for (int i = 0; i < v.size(); i++) {
		params p = v[i];
		if (p.d == 0)
			navigateEast(p.x, p.y, p.l);
		else if (p.d == 1)
			navigateNorth(p.x, p.y, p.l);
		else if (p.d == 2)
			navigateWest(p.x, p.y, p.l);
		else
			navigateSouth(p.x, p.y, p.l);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			total1 = min(total1, Dist[sidelength - 1][sidelength - 1][i][j]);
		}
	}

	cout << "The answer to part 1 is " << total1 << endl;
	v.clear();
	addToHeap(4, 0, 0, 0);
	addToHeap(0, 4, 0, 3);
	minlength = 4;
	maxlength = 10;
	for (int i = 0; i < v.size(); i++) {
		params p = v[i];
		if (p.d == 0)
			navigateEast(p.x, p.y, p.l);
		else if (p.d == 1)
			navigateNorth(p.x, p.y, p.l);
		else if (p.d == 2)
			navigateWest(p.x, p.y, p.l);
		else
			navigateSouth(p.x, p.y, p.l);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 3; j < 10; j++) {
			total2 = min(total2, Dist[sidelength - 1][sidelength - 1][i][j]);
		}
	}

	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}