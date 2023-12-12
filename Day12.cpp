#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

vector<int> lengths;
long long results[110][40];
long long nonogram(string s, int index, int cur);

int remaining(int cur) {//returns how much space the remaining lengths will take at minimum (for instance 2,4,5 will have remaining 13)
	int l = lengths.size();
	int answer = l - cur - 1; // account for periods between lengths
	for (cur; cur < l; cur++) {
		answer += lengths[cur];
	}
	return answer;
}

long long memoize(string s, int index, int cur) {// use memoization to avoid repeating work
	long long r = results[index][cur];
	if (r != -1)
		return r;
	else {
		r = nonogram(s, index, cur);
		results[index][cur] = r;
		return r;
	}
}

long long nonogram(string s, int index, int cur) {
	//for the given string s, starting at the given index and with number cur, returns the number of combinations remaining possible
	int size = s.size();
	long long answer = 0;
	while (index < size && s[index] == '.') {
		index++;
	}
	if (index < size) {
		int rem = remaining(cur);
		if (size - index < rem)//remaining numbers do not fit in rest of the string
			return 0;
		if (s[index] == '?' && (size - index) + 1 >= rem) {//try treating the ? as a '.' if there's enough room in the remainder of the string
			answer = memoize(s, index + 1, cur); 
		}
		int length = lengths[cur]; // if it is a ?, treat it as a hashtag
		if (index + length > size) { //the current length wouldn't fit in the rest of the string
			return answer;
		}
		index++;
		for (int i = 1; i < length; i++) {
			if (s[index] == '.')
				return answer;
			index++;
		}
		//we found a stretch of length hashtags (or ?s we treat as hashtags). Now we check if this was the last number
		//If it is, we check if the remainder of the string is only ',' or ?s. If so, found one combination, else not valid.
		cur++;
		if (cur == lengths.size()) {
			while (index < size) {
				if (s[index] == '#')
					return answer;
				index++;
			}
			return answer + 1;
		}

		//it wasn't the last length, so we check if the previous stretch was actually followed by a '.' (or ?) if not, fail. if true, continue recursively
		if (s[index] == '#') {
			return answer;
		}
		rem = remaining(cur);
		if ((size - index) + 1 >= rem) { //enough room in rest of the string for the rest of the numbers
			return answer += memoize(s, index + 1, cur);
		}
		return answer;
	}
	return 0; //reached the end of the string before hitting another stretch of # but there's still a number left to process
}

int main(int argc, char* argv[]) {
	long long total1 = 0;
	long long total2 = 0;
	ifstream f("data.txt");
	string s;
	string t;
	int i = 0;
	while (f >> s) {
		f >> t;
		stringstream ss(t);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			lengths.push_back(stoi(substr));
			//cout << substr << ",";
			
		}
		for (int i = 0; i < 110; i++) {
			for (int j = 0; j < 40; j++) {
				results[i][j] = -1;
			}
		}
		total1 += nonogram(s, 0, 0);
		string s2 = s + '?' + s + '?' + s + '?' + s + '?' + s;
		vector<int> v = lengths;
		for (int i = 0; i < 4; i++) {
			lengths.insert(lengths.end(), v.begin(), v.end());
		}
		for (int i = 0; i < 110; i++) {
			for (int j = 0; j < 40; j++) {
				results[i][j] = -1;
			}
		}
		long long r = nonogram(s2, 0, 0);
		total2 += r;
		lengths.clear();
		i++;

	}

	// something goes wrong with ?.??????????.?

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}

// 27855940973 too low