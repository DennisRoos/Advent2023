#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

struct node {
	int x;
	int y;
	vector<node*> neighbours; //nodes that this node has a path to
	vector<int> distances; // distance to the neighbours
	vector<node*> slopeneighbours; //nodes that this node has a path to if slopes are ignored
	vector<int> slopedistances; // distance to the slope neighbours
	bool visited;
};

int sidelength;
char map[141][141];
node* destination;

vector<node*> nodes; // the intersections where the path branches.

node* findNode(int x, int y) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->x == x && nodes[i]->y == y)
			return nodes[i];
	}
	node* n = new node();
	n->x = x;
	n->y = y;
	n->visited = false;
	nodes.push_back(n);
	if (y == sidelength - 1) {
		destination = n;
	}
	return n;
}

void traversePath(node* src, int x, int y, int direction, int depth) {
	while (map[x][y] == '.' && y < sidelength - 1) {
		if (direction == 0) { //coming from west
			if (map[x + 1][y] != '#') 
				x++;
			else if (map[x][y + 1] != '#') {
				y++;
				direction = 1;
			}
			else if (map[x][y - 1] != '#') {
				y--;
				direction = 3;
			}
		}
		else if (direction == 1) { //coming from north
			if (map[x][y + 1] != '#')
				y++;
			else if (map[x - 1][y] != '#') {
				x--;
				direction = 2;
			}
			else if (map[x + 1][y] != '#') {
				x++;
				direction = 0;
			}
		}
		else if (direction == 2) { //coming from east
			if (map[x - 1][y] != '#')
				x--;
			else if (map[x][y + 1] != '#') {
				y++;
				direction = 1;
			}
			else if (map[x][y - 1] != '#') {
				y--;
				direction = 3;
			}
		}
		else if (direction == 3) { //coming from south
			if (map[x][y - 1] != '#')
				y--;
			else if (map[x - 1][y] != '#') {
				x--;
				direction = 2;
			}
			else if (map[x + 1][y] != '#') {
				x++;
				direction = 0;
			}
		}
		depth++;
	}
	if (map[x][y] == '>') {
		depth++;
		x++;
	}
	if (map[x][y] == 'v') {
		depth++;
		y++;
	}
	node* dest = findNode(x, y);
	src->neighbours.push_back(dest);
	src->distances.push_back(depth);
	dest->slopeneighbours.push_back(src);
	dest->slopedistances.push_back(depth);
	return;
}

int longestPath(node* n, int length) {
	if (n == destination)
		return length;
	int longest = 0;
	for (int i = 0; i < n->neighbours.size(); i++) {
		int result = longestPath(n->neighbours[i], length + n->distances[i]);
		longest = max(longest, result);
	}
	return longest;
}

int longestPath2(node* n, int length) {
	if (n == destination)
		return length;
	if (n->visited)
		return -1;
	n->visited = true; //avoid crossing the same node (and thus the same tile) twice
	int longest = 0;
	for (int i = 0; i < n->neighbours.size(); i++) {
		int result = longestPath2(n->neighbours[i], length + n->distances[i]);
		longest = max(longest, result);
	}
	for (int i = 0; i < n->slopeneighbours.size(); i++) {
		int result = longestPath2(n->slopeneighbours[i], length + n->slopedistances[i]);
		longest = max(longest, result);
	}
	n->visited = false;
	return longest;
}

int main(int argc, char* argv[]) {
	sidelength = 141;
	long long total1 = 0;
	long long total2 = 0;
	string s;
	ifstream f("data.txt");
	for (int y = 0; y < sidelength; y++) {
		f >> s;
		for (int x = 0; x < sidelength; x++) {
			map[x][y] = s[x];
		}
	}
	node* n = findNode(1, 1);
	traversePath(n, 1, 1, 0, 1);

	for (int i = 1; i < nodes.size(); i++) {
		node* current = nodes[i];
		if (map[current->x + 1][current->y] == '>') {
			traversePath(current, current->x + 2, current->y, 0, 2);
		}
		if (current->y < sidelength - 1 && map[current->x][current->y + 1] == 'v') {
			traversePath(current, current->x, current->y + 2, 1, 2);
		}
	}

	total1 = longestPath(nodes[0], 0);
	cout << "The answer to part 1 is " << total1 << endl;
	total2 = longestPath2(nodes[0], 0);
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}