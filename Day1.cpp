#include <iostream>
#include <fstream>
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
		if (s[n] == 'o' && s[n + 1] == 'n' && s[n + 2] == 'e') {
			return 1;
		}
		if (s[n] == 't' && s[n + 1] == 'w' && s[n + 2] == 'o') {
			return 2;
		}
		if (s[n] == 's' && s[n + 1] == 'i' && s[n + 2] == 'x') {
			return 6;
		}
		if (n < size - 3) {
			if (s[n] == 'f' && s[n + 1] == 'o' && s[n + 2] == 'u' && s[n + 3] == 'r') {
				return 4;
			}
			if (s[n] == 'f' && s[n + 1] == 'i' && s[n + 2] == 'v' && s[n + 3] == 'e') {
				return 5;
			}
			if (s[n] == 'n' && s[n + 1] == 'i' && s[n + 2] == 'n' && s[n + 3] == 'e') {
				return 9;
			}
			if (s[n] == 'z' && s[n + 1] == 'e' && s[n + 2] == 'r' && s[n + 3] == 'o') {
				return 0;
			}
			if (n < size - 4) {
				if (s[n] == 't' && s[n + 1] == 'h' && s[n + 2] == 'r' && s[n + 3] == 'e' && s[n + 4] == 'e') {
					return 3;
				}
				if (s[n] == 's' && s[n + 1] == 'e' && s[n + 2] == 'v' && s[n + 3] == 'e' && s[n + 4] == 'n') {
					return 7;
				}
				if (s[n] == 'e' && s[n + 1] == 'i' && s[n + 2] == 'g' && s[n + 3] == 'h' && s[n + 4] == 't') {
					return 8;
				}

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
			cout << number << endl;
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