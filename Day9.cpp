#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

#include <algorithm> 

using namespace std;

int extrapolate(int A[], int n) {
	int B[21];
	bool zeroes = true;
	for (int i = 0; i < n - 1; i++) {
		B[i] = A[i + 1] - A[i];
		zeroes = zeroes && (B[i] == 0);
	}
	if (zeroes)
		return A[n - 1];
	return A[n - 1] + extrapolate(B, n - 1);
}

int main(int argc, char* argv[]) {
	int linesize = 21;
	ifstream f("data.txt");
	int A[21];
	int Rev[21];
	int total1 = 0;
	int total2 = 0;
	while (f >> A[0]) {
		Rev[linesize - 1] = A[0];
		for (int i = 1; i < linesize; i++) {
			f >> A[i];
			Rev[linesize - 1 - i] = A[i];
		}
		total1 += extrapolate(A, linesize);
		total2 += extrapolate(Rev, linesize);
	}
	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}