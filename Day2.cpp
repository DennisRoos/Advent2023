#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

int pos;



int main(int argc, char* argv[]) {

	int total1 = 0;
	int total2 = 0;
	string s;
	int num; 
	string color;
	ifstream f("data.txt");
	for (int game = 1; game <= 100; game++) {
		bool possible = true;
		int minred = 0;
		int mingreen = 0;
		int minblue = 0;
		f >> s;
		f >> s; //skip past preamble
		bool b = true;
		while (b) {
			f >> num;
			f >> color;
			if (color[0] == 'r') {
				if (num > 12)
					possible = false;
				minred = max(minred, num);
			}
			else if (color[0] == 'g') {
				if (num > 13)
					possible = false;
				mingreen = max(mingreen, num);
			}
			else if (color[0] == 'b') {
				if (num > 14)
					possible = false;
				minblue = max(minblue, num);
			}

			if (color.back() != ',' && color.back() != ';') //reached the end of the game
				b = false;
		}
		if (possible)
			total1 += game;
		total2 += minred * mingreen * minblue;
	}

	cout << "The answer for part 1 is " << total1 << endl;
	cout << "The answer for part 2 is " << total2 << endl;
	return 0;
}