#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int parse1(string s, int n) {
	if (s[n] >= '0' && s[n] <= '9') {
		return s[n] - '0';
	}
	else {
		return -1;
	}
}

int parse2(string s, int n) {
	int size = s.size();
	if (n < size - 2) {
		string s3 = s.substr(n, 3);
		if (s3.compare("one") == 0)
			return 1;
		if (s3.compare("two") == 0)
			return 2;
		if (s3.compare("six") == 0)
			return 6;
		if (n < size - 3) {
			string s4 = s.substr(n, 4);
			if (s4.compare("four") == 0)
				return 4;
			if (s4.compare("five") == 0)
				return 5;
			if (s4.compare("nine") == 0)
				return 9;
			if (n < size - 4) {
				string s5 = s.substr(n, 5);
				if (s5.compare("three") == 0)
					return 3;
				if (s5.compare("seven") == 0)
					return 7;
				if (s5.compare("eight") == 0)
					return 8;
			}
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int answer1 = 0;
		int answer2 = 0;
		while (infile >> s)
		{
			int i = 0;
			int digit1 = -1;
			while (digit1 == -1) {
				digit1 = parse1(s, i);
				i++;
			}
			int digit2 = -1;
			i = s.size() - 1;
			while (digit2 == -1) {
				digit2 = parse1(s, i);
				i--;
			}
			int number = (10 * digit1) + digit2;
			answer1 += number;
			i = 0;
			digit1 = -1;
			while (digit1 == -1) {
				digit1 = parse1(s, i);
				if (digit1 == -1) {
					digit1 = parse2(s, i);
				}
				i++;
			}
			digit2 = -1;
			i = s.size() - 1;
			while (digit2 == -1) {
				digit2 = parse1(s, i);
				if (digit2 == -1) {
					digit2 = parse2(s, i);
				}
				i--;
			}
			number = (10 * digit1) + digit2;
			answer2 += number;
		}
		//present final answer
		cout << "Final answer to part 1 is " << answer1 << "\n";
		cout << "Final answer to part 2 is " << answer2 << "\n";
	}
	else {
		cout << "can't find file?\n";
	}
}
