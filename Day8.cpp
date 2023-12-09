#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

#include <algorithm> 

using namespace std;

struct node {
	string name;
	node* left;
	node* right;
};

vector<node*> map;
vector<node*> startlist;
vector<node*> endlist;
node* start;
node* target;
string directions;
vector<long long> offset;
vector<long long> period;

node* addOrFindNode(string s) {
	for (int i = 0; i < map.size(); i++) {
		if (map[i]->name.compare(s) == 0) {
			return map[i];
		}
	}
	node* N = new node();
	N->name = s;
	if (s[2] == 'A')
		startlist.push_back(N);
	if (s[2] == 'Z')
		endlist.push_back(N);
	if (s.compare("AAA") == 0)
		start = N;
	if (s.compare("ZZZ") == 0)
		target = N;
	map.push_back(N);
	return N;
}

void navigate1() {
	int cur = 0;
	node* N = start;
	int depth = 0;
	while (N != target) {
		if (directions[cur] == 'L') {
			N = N->left;
		}
		else {
			N = N->right;
		}
		cur = (cur + 1) % directions.size();
		depth++;
	}
	cout << "Found ZZZ after " << depth << " steps!" << endl;
	return;
}

bool AtEnd(node* n) {
	for (int i = 0; i < endlist.size(); i++) {
		if (n == endlist[i])
			return true;
	}
	return false; 
}

long long navigate2(node* N) {
	int cur = 0;
	long long depth = 0;
	bool Done = false;
	while (!Done) {
		if (directions[cur] == 'L') {
			N = N->left;
			Done = AtEnd(N);
		}
		else {
			N = N->right;
			Done = AtEnd(N);
		}
		cur = (cur + 1) % directions.size();
		depth++;
	}
	return depth;
}

long long gcd(long long a, long long b){
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main(int argc, char* argv[]) {
	ifstream f("data.txt");
	string s;
	string l;
	string r;
	f >> directions;
	while (f >> s) {
		f >> l;
		f >> l;
		f >> r;
		l = l.substr(1, l.size() - 2);//cut off parentheses etc
		r = r.substr(0, r.size() - 1);
		node* N = addOrFindNode(s);
		N->left = addOrFindNode(l);
		N->right = addOrFindNode(r);
	}
	navigate1();
	for (int i = 0; i < startlist.size(); i++) {
		long long p = navigate2(startlist[i]);
		period.push_back(p);
	}
	long long total2 = period[0];
	for (int i = 1; i < period.size(); i++)
		total2 = (period[i] * total2) / (gcd(period[i], total2));
	cout << "Total for part 2 was " << total2 << endl;
	return 0;
}