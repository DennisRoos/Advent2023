#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

struct brick {
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int zmin;
	int zmax;
	int num;
	bool present;
	vector<brick*> children;// bricks underneath this brick
	vector<brick*> parents;// bricks above this brick
};

vector<brick*> bricks;
brick* Column[10][10][400];

struct less_than_brick
{
	inline bool operator() (const brick* b1, const brick* b2)
	{
		if (b1->zmin != b1->zmin)
			return (b1->zmin < b2->zmin);
		return (b1->zmax < b2->zmax);
	}
};

bool resting(brick* b) {
	if (b->zmin <= 1)//on the floor
		return true;
	for (int x = b->xmin; x <= b->xmax; x++) {
		for (int y = b->ymin; y <= b->ymax; y++) {
			if (Column[x][y][b->zmin - 1] != 0)
				return true;
		}
	}
	return false;
}

void fall(brick* b) {
	while (!resting(b)) {
		for (int z = b->zmin; z <= b->zmax; z++) {
			for (int x = b->xmin; x <= b->xmax; x++) {
				for (int y = b->ymin; y <= b->ymax; y++) {
					Column[x][y][z - 1] = b;
					Column[x][y][z] = NULL;
				}
			}
		}
		b->zmin--;
		b->zmax--;
	}
}

void addParent(brick* b, brick* c) {
	for (int i = 0; i < b->parents.size();i++) {
		if (b->parents[i] == c)
			return;
	}
	b->parents.push_back(c);
}

void addChild(brick* b, brick* c) {
	for (int i = 0; i < b->children.size();i++) {
		if (b->children[i] == c)
			return;
	}
	b->children.push_back(c);
}

void setChildren(brick* b) {
	for (int x = b->xmin; x <= b->xmax; x++) {
		for (int y = b->ymin; y <= b->ymax; y++) {
			brick* c = Column[x][y][b->zmin - 1];
			if (c != NULL) {
				addChild(b, c);
				addParent(c, b);
 			}
		}
	}
}

bool canDisintegrate(brick* b) {
	for (int i = 0; i < b->parents.size(); i++) {
		if (b->parents[i]->children.size() == 1)
			return false;
	}
	return true;
}

bool nowFalling(brick* b) {
	for (int i = 0; i < b->children.size(); i++) {
		if (b->children[i]->present)
			return false;
	}
	return true;
}

int recursiveDisintegrate(brick* b) {
	b->present = false;
	int answer = 0;
	for (int i = 0; i < b->parents.size(); i++) {
		if (nowFalling(b->parents[i])) {
			answer += 1 + recursiveDisintegrate(b->parents[i]);
		}
	}
	return answer;
}

int main(int argc, char* argv[]) {
	long long total1 = 0;
	long long total2 = 0;
	for (int z = 0; z < 400; z++) {
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				Column[x][y][z] = NULL;
			}
		}
	}
	regex re("(\\d+),(\\d+),(\\d+)~(\\d+),(\\d+),(\\d+)");
	smatch match;
	string s;
	ifstream f("data.txt");
	while (f >> s) {
		if (regex_search(s, match, re) == true) {
			brick* b = new brick();
			b->xmin = stoi(match.str(1));
			b->xmax = stoi(match.str(4));
			b->ymin = stoi(match.str(2));
			b->ymax = stoi(match.str(5));
			b->zmin = stoi(match.str(3));
			b->zmax = stoi(match.str(6));
			b->present = true;
			bricks.push_back(b);
			for (int z = b->zmin; z <= b->zmax; z++) {
				for (int x = b->xmin; x <= b->xmax; x++) {
					for (int y = b->ymin; y <= b->ymax; y++) {
						Column[x][y][z] = b;
					}
				}
			}
		}
	}
	sort(bricks.begin(), bricks.end(), less_than_brick());
	for (int i = 0; i < bricks.size(); i++) {
		fall(bricks[i]);
	}

	for (int i = 0; i < bricks.size(); i++) {
		setChildren(bricks[i]);
	}

	for (int i = 0; i < bricks.size(); i++) {
		if (canDisintegrate(bricks[i])) 
			total1++;
		total2 += recursiveDisintegrate(bricks[i]);
		for (int j = 0; j < bricks.size(); j++) {
			bricks[j]->present = true;
		}
	}

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}