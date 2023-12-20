#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <sstream>
#include <algorithm> 

using namespace std;

enum moduleType {
	BROADCASTER,
	FLIPFLOP,
	CONJUNCTION,
};

struct module {
	string name;
	bool state;
	moduleType type;
	vector<module*> dest;
	vector<module*> inputs;//for conjunction
	vector<bool> inputstates;
	module(string n) {
		state = false;
		name = n;
	}
};

struct message {
	module* sender;
	module* receiver;
	bool pulse;
};

vector<module*> modules;
vector<message> messagelist;
long long lowpulses;
long long highpulses;
long long buttonpresses;
vector<long long> periods;
vector<module*> conjunctors;

void sendmessages(module* sender, bool pulse) {
	for (int i = 0; i < sender->dest.size(); i++) {
		message m = message();
		m.sender = sender;
		m.pulse = pulse;
		m.receiver = sender->dest[i];
		messagelist.push_back(m);
	}
	if (pulse)
		highpulses += sender->dest.size();
	else
		lowpulses += sender->dest.size();
	return;
}

void processMessage(module* sender, module* r, bool pulse) {
	/*string payload = "low";
	if (pulse)
		payload = "high";
	cout << sender->name << " -" << payload << "-> " << r->name << endl;*/
	if (r->type == BROADCASTER) {
		r->state = pulse;
	}
	else if (r->type == FLIPFLOP) {
		if (pulse) //high pulses are ignored
			return;
		r->state = !r->state;
	}
	else if (r->type == CONJUNCTION) {
		for (int i = 0; i < r->inputs.size(); i++) {
			if (r->inputs[i] == sender) {
				r->inputstates[i] = pulse;
				break;
			}
		}
		bool b = true;
		for (int i = 0; i < r->inputs.size(); i++) {
			b = b && r->inputstates[i];
		}
		
		if (b) {
			for (int i = 0; i < conjunctors.size(); i++) {
				if (conjunctors[i] == r) {
					periods.push_back(buttonpresses);
					cout << "Found a cycle for conjunctor " << conjunctors[i]->name << " at " << buttonpresses << endl;
				}
			}
		}
		r->state = !b; //if all high pulses, broadcast a low pulse
	}
	sendmessages(r, r->state);
	return;
}

module* findModule(string name) {
	for (int i = 0; i < modules.size(); i++) {
		if (modules[i]->name.compare(name) == 0)
			return modules[i];
	}
	module* m = new module(name);
	modules.push_back(m);
	return m;
}

module* getNext(module* m, module* con) { //gets the next module in the sequence, i.e. the output that is not con. Returns NULL if last in sequence
	if (m->dest.size() == 1) {//only one output
		if (m->dest[0] == con)
			return NULL;
		else
			return m->dest[0];
	}
	else {//two outputs
		if (m->dest[0] == con)
			return m->dest[1];
		else
			return m->dest[0];
	}
}

bool isOutput(module* src, module* target) { //returns if target is an output of source
	for (int i = 0; i < src->dest.size(); i++) {
		if (src->dest[i] == target)
			return true;
	}
	return false;
}

long long findPeriod(module* m) {
	//start module always has two outputs, one of which is the conjunction module, the other the next in the sequence of flip-flops
	module* con;
	if (m->dest[0]->type == CONJUNCTION)
		con = m->dest[0];
	else
		con = m->dest[1];
	long long num = 0; 
	while (m != NULL) {
		num *= 2;
		module* next = getNext(m, con);
		if (isOutput(m, con))
			num++;
		m = getNext(m, con);
	}
	return num;
}

module* findCon(module* m) {
	if (m->dest[0]->type == CONJUNCTION)
		return m->dest[0];
	else
		return m->dest[1];
}

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main(int argc, char* argv[]) {
	long long total1 = 0;
	lowpulses = 1000;
	highpulses = 0;
	string s;
	ifstream f("data.txt");
	while (f >> s) {
		moduleType type = BROADCASTER;
		if (s[0] == '%') {
			type = FLIPFLOP;
			s.erase(0, 1);
		}
		else if (s[0] == '&') {
				type = CONJUNCTION;
				s.erase(0, 1);
			}
		module* m = findModule(s);
		m->type = type;
		f >> s; //skip past the arrow
		bool b = true;
		while (b) {
			f >> s;
			if (s.back() == ',')
				s.pop_back();
			else //last destination
				b = false;
			module* target = findModule(s);
			m->dest.push_back(target);
		}
	}

	for (int k = 0; k < modules.size(); k++) { // have to set up the inputs for conjunction modules
		if (modules[k]->type == CONJUNCTION) {
			for (int i = 0; i < modules.size(); i++) {
				for (int j = 0; j < modules[i]->dest.size(); j++) {
					if (modules[i]->dest[j] == modules[k]) {
						modules[k]->inputs.push_back(modules[i]);
						modules[k]->inputstates.push_back(false);
						cout << modules[i]->name << ", " << modules[k]->name << endl;
					}
				}
			}
		}
	}
	module* broadcaster = findModule("broadcaster");
	module* button = new module("button");
	message initial = message();
	initial.sender = button;
	initial.pulse = false;
	initial.receiver = broadcaster;

	int numberOfCycles = broadcaster->dest.size();
	for (int i = 0; i < numberOfCycles; i++) {
		conjunctors.push_back(findCon(broadcaster->dest[i]));
		cout << conjunctors[i]->name << endl;
	}
	buttonpresses = 1;
	while (periods.size() < numberOfCycles){

		messagelist.push_back(initial);
		for (int j = 0; j < messagelist.size(); j++) {
			message m = messagelist[j];
			processMessage(m.sender, m.receiver, m.pulse);
		}
		messagelist.clear();
		if (buttonpresses == 1000) {
			total1 = lowpulses * highpulses;
			cout << "The answer to part 1 is " << total1 << endl;
		}
		buttonpresses++;
	}



	long long total2 = periods[0];
	for (int i = 1; i < periods.size(); i++)
		total2 = (periods[i] * total2) / (gcd(periods[i], total2));


	cout << "The answer to part 2 is " << total2 << endl;
	return 0;
}

// 709255536979 too low