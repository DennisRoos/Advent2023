#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;
struct workflow;

struct part {
	int x;
	int m;
	int a;
	int s;
};

struct rule {
	char c;				//which attribute should be checked for
	bool greaterThan;	//greater than or less than
	int value;			//value to be compared against
	workflow* next;		//workflow to go to for success
};

struct workflow {
	string name;
	vector<rule*> rules;
	workflow* final;
};

struct plane {
	long long xmin; 
	long long xmax;
	long long mmin;
	long long mmax;
	long long amin;
	long long amax;
	long long smin;
	long long smax;
};

vector<workflow*> workflows;

workflow* findWorkflow(string name) {
	for (int i = 0; i < workflows.size(); i++) {
		if (workflows[i]->name.compare(name) == 0)
			return workflows[i];
	}
	workflow* w = new workflow();
	w->name = name;
	workflows.push_back(w);
	return w;
}

bool accept(part p, workflow* w) {
	if (w->name.compare("A") == 0)
		return true;
	if (w->name.compare("R") == 0)
		return false;
	for (int i = 0; i < w->rules.size(); i++) {
		rule* r = w->rules[i];
		int value;
		if (r->c == 'x')//determine attribute
			value = p.x;
		else if (r->c == 'm')
			value = p.m;
		else if (r->c == 'a')
			value = p.a;
		else if (r->c == 's')
			value = p.s;
		bool b;
		if (r->greaterThan) 
			b = (value > r->value);//determine if part passes this rule
		else 
			b = (value < r->value);
		
		if (b)
			return accept(p, r->next);//if it passes, go to next rule
	}
	return accept(p, w->final);
}

long long total2;

void acceptRange(workflow* w, plane p) {

	if (w->name.compare("A") == 0) {
		long long combinations = (p.xmax - p.xmin + 1) * (p.mmax - p.mmin + 1) * (p.amax - p.amin + 1) * (p.smax - p.smin + 1);
		total2 += combinations;
		return;
	}
	if (w->name.compare("R") == 0)
		return;
	for (int i = 0; i < w->rules.size(); i++) {
		rule* r = w->rules[i];
		plane newplane = p;
		if (r->greaterThan) {
			if (r->c == 'x') {
				if (p.xmin > r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.xmax > r->value) { // part of the plane fits within this rule. Gotta split
					newplane.xmin = r->value + 1;
					acceptRange(r->next, newplane);
					p.xmax = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
			else if (r->c == 'm') {
				if (p.mmin > r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.mmax > r->value) { // part of the plane fits within this rule. Gotta split
					newplane.mmin = r->value + 1;
					acceptRange(r->next, newplane);
					p.mmax = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
			else if (r->c == 'a') {
				if (p.amin > r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.amax > r->value) { // part of the plane fits within this rule. Gotta split
					newplane.amin = r->value + 1;
					acceptRange(r->next, newplane);
					p.amax = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
			else if (r->c == 's') {
				if (p.smin > r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.smax > r->value) { // part of the plane fits within this rule. Gotta split
					newplane.smin = r->value + 1;
					acceptRange(r->next, newplane);
					p.smax = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
		}

		else { // rule is smaller than
			if (r->c == 'x') {
				if (p.xmax < r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.xmin < r->value) { // part of the plane fits within this rule. Gotta split
					newplane.xmax = r->value - 1;
					acceptRange(r->next, newplane);
					p.xmin = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
			else if (r->c == 'm') {
				if (p.mmax < r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.mmin < r->value) { // part of the plane fits within this rule. Gotta split
					newplane.mmax = r->value - 1;
					acceptRange(r->next, newplane);
					p.mmin = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
			else if (r->c == 'a') {
				if (p.amax < r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.amin < r->value) { // part of the plane fits within this rule. Gotta split
					newplane.amax = r->value - 1;
					acceptRange(r->next, newplane);
					p.amin = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
			else if (r->c == 's') {
				if (p.smax < r->value) { // entire plane fits within this rule
					acceptRange(r->next, p);
					return; // nothing left to do in this workflow
				}
				else if (p.smin < r->value) { // part of the plane fits within this rule. Gotta split
					newplane.smax = r->value - 1;
					acceptRange(r->next, newplane);
					p.smin = r->value; //continue in this workflow with the part of p that didn't pass the rule
				}
			}
		}
	}
	acceptRange(w->final, p);
}

int main(int argc, char* argv[]) {
	long long total1 = 0;
	total2 = 0;
	string s;
	ifstream f("data.txt");
	f >> s;
	regex re("([a-z]+)\\{(.+)\\}");
	smatch match;
	workflow* Accept = new workflow();
	Accept->name = "A";
	workflows.push_back(Accept);
	workflow* Reject = new workflow();
	Reject->name = "R";
	workflows.push_back(Reject);
	while (regex_search(s, match, re) == true) {
		string name = match.str(1);
		string inner = match.str(2);
		workflow* w = findWorkflow(name);
		stringstream ss(inner);
		while (ss.good()) {
			string word;
			getline(ss, word, ',');
			regex ruleregex("([a-z])(<|>)(\\d+):([a-zA-Z]+)");
			if (regex_search(word, match, ruleregex) == true) {
				char c = match.str(1)[0];
				char sign = match.str(2)[0];
				int value = stoi(match.str(3));
				string target = match.str(4);
				rule* r = new rule();
				r->c = c;
				r->greaterThan = (sign == '>');
				r->value = value;
				r->next = findWorkflow(target);
				w->rules.push_back(r);
			}
			else {//last rule
				w->final = findWorkflow(word);
			}
		}
		f >> s;
	}
	workflow* start = findWorkflow("in");
	regex partline("\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}"); //way too many escapes
	do {
		if (regex_search(s, match, partline) == true) {
			part p = part();
			p.x = stoi(match.str(1));
			p.m = stoi(match.str(2));
			p.a = stoi(match.str(3));
			p.s = stoi(match.str(4));
			if (accept(p, start)) {
				total1 += p.x + p.m + p.a + p.s;
			}
		}

	} while (f >> s);

	plane p = plane();
	p.xmin = 1;
	p.mmin = 1;
	p.amin = 1;
	p.smin = 1;
	p.xmax = 4000;
	p.mmax = 4000;
	p.amax = 4000;
	p.smax = 4000;

	acceptRange(start, p);

	cout << "The answer to part 1 is " << total1 << endl;
	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}