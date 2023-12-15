#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

struct lens {
	string name;
	int focalLength;
};

vector<lens> boxes[256];

void HASHMAPadd(int hash, string name, int focal) {
	for (int i = 0; i < boxes[hash].size(); i++) {
		if (name.compare(boxes[hash][i].name) == 0) {
			boxes[hash][i].focalLength = focal;
			return;
		}
	}
	//lens was not in this box yet
	lens l = lens();
	l.name = name;
	l.focalLength = focal;
	boxes[hash].push_back(l);
	return;
}

void HASHMAPremove(int hash, string name) {
	for (int i = 0; i < boxes[hash].size(); i++) {
		if (name.compare(boxes[hash][i].name) == 0) {
			boxes[hash].erase(boxes[hash].begin() + i);
			return;
		}
	}
	return;
}

int HASH(string s) {
	int current = 0;
	for (int i = 0; i < s.size(); i++) {
		current += s[i];
		current *= 17;
		current = current % 256;
	}
	return current;
}

int main(int argc, char* argv[]) {
	long long total1 = 0;
	long long total2 = 0;
	ifstream f("data.txt");
	string t;
	int i = 0;
	f >> t;
	stringstream ss(t);
	while (ss.good()) {
		string word;
		getline(ss, word, ',');
		int hash = HASH(word);
		total1 += hash;
		char last = word.back();
		if (last == '-') {//it's a remove command
			word.pop_back(); //remove the '-'
			hash = HASH(word);
			HASHMAPremove(hash, word);
		}
		else {//it's an add command
			int focal = last - '0';
			word.pop_back(); //remove the number
			word.pop_back(); //remove the '='
			hash = HASH(word);
			HASHMAPadd(hash, word, focal);
		}
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < boxes[i].size(); j++) {
			int power = (i + 1) * (j + 1) * boxes[i][j].focalLength;
			total2 += power;
		}
	}

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}