#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

int sidelength;
bool map[131][131];
int Sx;
int Sy;

void step(bool A[131][131], bool B[131][131]) {

	for (int i = 0; i < sidelength; i++) {
		for (int j = 0; j < sidelength; j++) {
			B[i][j] = false;
		}
	}
	for (int i = 0; i < sidelength; i++) {
		for (int j = 0; j < sidelength; j++) {
			if (A[i][j]) {
				if (i > 0 && map[i - 1][j])
					B[i - 1][j] = true;
				if (i < 130 && map[i + 1][j])
					B[i + 1][j] = true;
				if (j > 0 && map[i][j - 1])
					B[i][j - 1] = true;
				if (j < 130 && map[i][j + 1])
					B[i][j + 1] = true;
			}
		}
	}
}

long long traverse(int x, int y, long long steps) {//returns how many tiles are reached within one map when starting at (x,y) and walking for 'steps' steps.
	if (steps == 0)
		return 1;
	bool A[131][131];
	bool B[131][131];
	for (int i = 0; i < sidelength; i++) {
		for (int j = 0; j < sidelength; j++) {
			A[i][j] = false;
		}
	}
	A[x][y] = true;
	for (int k = 0; k < steps; k++) {
		step(A, B);
		for (int i = 0; i < sidelength; i++) {
			for (int j = 0; j < sidelength; j++) {
				A[i][j] = B[i][j];
			}
		}
	}
	long long count = 0;
	for (int i = 0; i < sidelength; i++) {
		for (int j = 0; j < sidelength; j++) {
			if (A[i][j])
				count++;
		}
	}
	cout << "entrance at " << x << "," << y << " with " << steps << " steps reaches " << count << " tiles." << endl;
	return count;
}


int main(int argc, char* argv[]) {
	sidelength = 131;
	long long totalsteps = 26501365;
	long long total1 = 0;
	long long total2 = 0;
	string s;
	ifstream f("data.txt");
	for (int y = 0; y < sidelength; y++) {
		f >> s;
		for (int x = 0; x < sidelength; x++) {
			if (s[x] == '#')
				map[x][y] = false;
			else
				map[x][y] = true;
			if (s[x] == 'S') {
				Sx = x;
				Sy = y;
			}
		}
	}
	total1 = traverse(Sx, Sy, 64);
	long long fullodd = traverse(130, 65, 261);
	long long fulleven = traverse(65, 130, 262);

	long long west = traverse(0, 65, (totalsteps - 66) % 131);
	long long north = traverse(65, 0, (totalsteps - 66) % 131);
	long long east = traverse(130, 65, (totalsteps - 66) % 131);
	long long south = traverse(65, 130, (totalsteps - 66) % 131);

	long long southeastfar = traverse(0, 0, (totalsteps - 132) % 131);
	long long northeastfar = traverse(0, 130, (totalsteps - 132) % 131);
	long long southwestfar = traverse(130, 0, (totalsteps - 132) % 131);
	long long northwestfar = traverse(130, 130, (totalsteps - 132) % 131);

	long long southeastnear = traverse(0, 0, ((totalsteps - 132) % 131) + 131);
	long long northeastnear = traverse(0, 130, ((totalsteps - 132) % 131) + 131);
	long long southwestnear = traverse(130, 0, ((totalsteps - 132) % 131) + 131);
	long long northwestnear = traverse(130, 130, ((totalsteps - 132) % 131) + 131);

	long long num_blocks = totalsteps / 131;

	total2 = (num_blocks - 1) * (num_blocks - 1) * fulleven;
	cout << "full even blocks: " << (num_blocks - 1) * (num_blocks - 1) << " * " << fulleven << " = " << total2 << endl;

	total2 += num_blocks * num_blocks * fullodd;
	cout << "full odd blocks: " << num_blocks * num_blocks << " * " << fullodd << " = " << num_blocks * num_blocks * fullodd << endl;

	total2 += north + west + east + south;
	cout << "cardinal endpoints: " << north + west + east + south << endl;
	total2 += (num_blocks) * (southwestfar + northwestfar + northeastfar + southeastfar);
	cout << "far blocks: " << (num_blocks) << " * " << (southwestfar + northwestfar + northeastfar + southeastfar) << endl;
	total2 += (num_blocks - 1) * (northwestnear + southwestnear + northeastnear + southeastnear);
	cout << "near blocks: " << (num_blocks - 1) << " * " << (northwestnear + southwestnear + northeastnear + southeastnear) << endl;
	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}