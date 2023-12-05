#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

vector<long long> source[7];//transition maps for each of the 7 transitions
vector<long long> dest[7];
vector<long long> length[7];
vector<long long> seeds;
vector<long long> seedstarts[8];//seedranges in each stage for part 2
vector<long long> seedlengths[8];

long long transitionSingle(long long current, int i) {
	// for a given value in stage i, return the value in stage i+1
	for (int j = 0; j < source[i].size(); j++) {
		if (current >= source[i][j] && current <= source[i][j] + length[i][j]) { // found a match
			long long diff = current - source[i][j];
			return dest[i][j] + diff;
		}
	}
	return current; // no matching map, so return the identity
}

void transitionRange(long long start, long long l, int i) {
	// for a given range in stage i, creates the ranges that result in stage i+1
	long long end = start + l - 1;
	for (int j = 0; j < source[i].size(); j++) {
		long long breakpoint = source[i][j] + length[i][j];
		if (start >= source[i][j] && start < breakpoint) { // start of the range is in this map
			if (end >= breakpoint) { // end of the range is beyond this map, gotta split into two ranges
				transitionRange(breakpoint, end - breakpoint + 2, i);
				l = breakpoint - start;
			}
			long long nextstart = dest[i][j] + (start - source[i][j]);
			seedstarts[i + 1].push_back(nextstart);
			seedlengths[i + 1].push_back(l);
			return;
		}
		else if (start < source[i][j] && end >= source[i][j]){ // range starts before this map, but overlaps either partially or completely. Gotta split into two ranges
			long long firstlength = source[i][j] - start;
			long long secondlength = l - firstlength;
			transitionRange(start, firstlength, i);
			transitionRange(source[i][j], secondlength, i);
			return;
		}
	}
	seedstarts[i + 1].push_back(start); //range was not in any of the maps, so it stays the same for the next stage
	seedlengths[i + 1].push_back(l);
}

int main(int argc, char* argv[]) {
	long long total1 = 9999999999;
	long long total2 = 9999999999;
	string s;
	ifstream f("data.txt");
	f >> s;
	f >> s;
	while (s[0] >= '0' && s[0] <= '9') {
		long long n = stoll(s);
		seeds.push_back(n);
		f >> s;
	}
	f >> s;
	int i = 0;
	while (f >> s) { //initialization
		if (s[0] >= '0' && s[0] <= '9') {
			long long d = stoll(s);
			dest[i].push_back(d);
			long long src;
			long long l;
			f >> src;
			f >> l;
			source[i].push_back(src);
			length[i].push_back(l);
		}
		else {
			f >> s;
			i++;
		}
	}

	for (int seed = 0; seed < seeds.size(); seed++) {
		long long current = seeds[seed];
		for (int i = 0; i < 7; i++) {
			current = transitionSingle(current, i);
		}
		total1 = min(total1, current);
	}

	for (int seed = 0; seed < seeds.size(); seed++) { //initialize for part 2
		seedstarts[0].push_back(seeds[seed]);
		seed++;
		seedlengths[0].push_back(seeds[seed]);
	}

	for (int i = 0; i < 7; i++) { //process all ranges for each stage
		for (int j = 0; j < seedstarts[i].size(); j++) {
			transitionRange(seedstarts[i][j], seedlengths[i][j], i);
		}
	}
	
	for (int i = 0; i < seedstarts[7].size(); i++) {// find first range in the final stage
		total2 = min(total2, seedstarts[7][i]);
	}

	cout << "The answer for part 1 is " << total1 << endl;
	cout << "The answer for part 2 is " << total2 << endl;
	return 0;
}