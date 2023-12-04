#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
	int total1 = 0;
	int total2 = 0;
	ifstream f("data.txt");
	int A[10];
	int wins[218]; // number of matching numbers on each card
	int numcards[218]; //number of copies of each card
	string s;
	int n;

	for (int i = 0; i < 218; i++) {
		numcards[i] = 1;
	}

	for (int game = 0; game < 218; game++) {
		int score = 0;
		int matches = 0;
		f >> s;
		f >> s; // skip past preamble
		for (int i = 0; i < 10; i++) {
			f >> n;
			A[i] = n;
		}
		f >> s; // skip past separator symbol
		for (int i = 0; i < 25; i++) {
			f >> n;
			for (int j = 0; j < 10; j++) {
				if (n == A[j]) {
					matches++;
					if (score == 0)
						score = 1;
					else
						score *= 2;
					break;
				}
			}
		}
		total1 += score;
		int num = numcards[game];
		total2 += num; // later cards can never increase the count of earlier cards, so we can add now
		for (int j = 1; j <= matches && game + j < 218; j++) {
			numcards[game + j] += num;
		}
	}

	cout << "The answer for part 1 is " << total1 << endl;
	cout << "The answer for part 2 is " << total2 << endl;
	return 0;
}