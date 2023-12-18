#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;



int main(int argc, char* argv[]) {
	long long total1 = 2;
	long long total2 = 2;
	long long x1 = 0;
	long long y1 = 0;
	long long x2 = 0;
	long long y2 = 0;
	vector<long long> vX1;
	vector<long long> vY1;
	vector<long long> vX2;
	vector<long long> vY2;
	ifstream f("data.txt");
	char c;
	long long n;
	string s;
	vX1.push_back(0);
	vY1.push_back(0);
	vX2.push_back(0);
	vY2.push_back(0);
	while (f >> c) {
		f >> n;
		f >> s;
		total1 += n;//parse for part 1
		if (c == 'U')
			y1 -= n;
		else if (c == 'D')
			y1 += n;
		else if (c == 'L')
			x1 -= n;
		else if (c == 'R')
			x1 += n;
		vX1.push_back(x1);
		vY1.push_back(y1);
		//parse for part 2
		c = s[7];
		s = s.substr(2, 5);
		stringstream ss;
		ss << hex << s;
		ss >> n;
		total2 += n;
		if (c == '3')
			y2 -= n;
		else if (c == '1')
			y2 += n;
		else if (c == '2')
			x2 -= n;
		else if (c == '0')
			x2 += n;
		vX2.push_back(x2);
		vY2.push_back(y2);
	}

	for (int i = 1; i < vX1.size() - 1; i++) {
		total1 += (vY1[i] + vY1[i + 1]) * (vX1[i] - vX1[i + 1]);
		total2 += (vY2[i] + vY2[i + 1]) * (vX2[i] - vX2[i + 1]);
	}
	total1 = abs(total1) / 2;
	total2 = abs(total2) / 2;

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}