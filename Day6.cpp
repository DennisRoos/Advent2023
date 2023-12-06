#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;


int game(long long t, long long r) {
	int count = 0;
	for (long long i = 1; i < t; i++) {
		long long distance = i * (t - i);
		if (distance > r)
			count++;
	}
	return count;
}

int main(int argc, char* argv[]) {
	vector<long long> times;
	vector<long long> records;
	int total1 = 1;
	int total2 = 1;
	string s;
	ifstream f("data.txt");
	f >> s;
	f >> s;
	string time = "";
	string record = "";
	while (s[0] >= '0' && s[0] <= '9') {
			int t = stoll(s);
			times.push_back(t);
			time.append(s);
			f >> s;
	}
	while (f >> s) {
		records.push_back(stoll(s));
		record.append(s);
	}

	for (int i = 0; i < times.size(); i++) {
		total1 *= game(times[i], records[i]);
	}
	total2 = game(stoi(time), stoll(record));

	cout << "The answer for part 1 is " << total1 << endl;
	cout << "The answer for part 2 is " << total2 << endl;
	return 0;
}