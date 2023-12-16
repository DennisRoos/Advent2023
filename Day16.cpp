#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

char Map[110][110];
bool Energized[110][110][4];
int sidelength;


void lightbeam(int x, int y, int direction) {
	while (x >= 0 && x < sidelength && y >= 0 && y < sidelength && !Energized[x][y][direction]) { // not leaving the board or having already visited
		Energized[x][y][direction] = true;
		if (Map[x][y] == char(92)) { // backslash '\'
			if (direction == 0) //going east
				direction = 1;
			else if (direction == 1) //going south
				direction = 0;
			else if (direction == 2) //going west
				direction = 3;
			else if (direction == 3) //going north
				direction = 2;
		}
		else if (Map[x][y] == '/') {
			if (direction == 0) //going east
				direction = 3;
			else if (direction == 1) //going south
				direction = 2;
			else if (direction == 2) //going west
				direction = 1;
			else if (direction == 3) //going north
				direction = 0;
		}
		else if (Map[x][y] == '|' && (direction == 0 || direction == 2)) {
			lightbeam(x, y - 1, 3);//split off north
			direction = 1; // This branch goes south
		}
		else if (Map[x][y] == '-' && (direction == 1 || direction == 3)) {
			lightbeam(x - 1, y, 2);//split off west
			direction = 0; // This branch goes east
		}

		if (direction == 0)
			x++;
		else if (direction == 1)
			y++;
		else if (direction == 2)
			x--;
		else if (direction == 3)
			y--;
	}
	return;
}

int countEnergized(int x, int y, int d) {
	lightbeam(x, y, d);
	int count = 0;
	for (int y = 0; y < sidelength; y++) {
		for (int x = 0; x < sidelength; x++) {
			if (Energized[x][y][0] || Energized[x][y][1] || Energized[x][y][2] || Energized[x][y][3])
				count++;
			Energized[x][y][0] = false;
			Energized[x][y][1] = false;
			Energized[x][y][2] = false;
			Energized[x][y][3] = false;
		}
	}
	return count;
}

int main(int argc, char* argv[]) {
	int total1 = 0;
	int total2 = 0;
	sidelength = 110;
	ifstream f("data.txt");
	string s;
	for (int y = 0; y < sidelength; y++) {
		f >> s;
		for (int x = 0; x < sidelength; x++) {
			Map[x][y] = s[x];
			Energized[x][y][0] = false;
			Energized[x][y][1] = false;
			Energized[x][y][2] = false;
			Energized[x][y][3] = false;
		}
	}
	total1 = countEnergized(0,0,0);
	for (int i = 0; i < sidelength; i++) {
		total2 = max(countEnergized(0, i, 0), total2);//left side
		total2 = max(countEnergized(sidelength - 1, i, 2), total2);//right side
		total2 = max(countEnergized(i, 0, 1), total2);//top side
		total2 = max(countEnergized(i, sidelength - 1, 3), total2);//bottom side
	}

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}