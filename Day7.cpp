#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

enum type {
	HighCard,
	OnePair,
	TwoPair,
	ThreeKind,
	FullHouse,
	FourKind,
	FiveKind
};

enum card {
	Joker,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

struct hand
{
	type t;
	type t2; //hand for rules in part 2;
	card strength[5];
	card strength2[5];
	long long bid;
};

card RateCard(char c) {
	if (c == 'A')
		return Ace;
	if (c == 'K')
		return King;
	if (c == 'Q')
		return Queen;
	if (c == 'J')
		return Jack;
	if (c == 'T')
		return Ten;
	if (c == '9')
		return Nine;
	if (c == '8')
		return Eight;
	if (c == '7')
		return Seven;
	if (c == '6')
		return Six;
	if (c == '5')
		return Five;
	if (c == '4')
		return Four;
	if (c == '3')
		return Three;
	if (c == '2')
		return Two;
}

type RateHand(string h) {
	string s = h;
	sort(s.begin(), s.end());
	int Count[6];
	for (int i = 0; i < 6; i++) 
		Count[i] = 0;
	int i = 1;
	int count = 1;
	char c = s[0];
	while (i < 5) {
		if (s[i] == c)
			count++;
		else {
			c = s[i];
			Count[count]++;
			count = 1;
		}
		i++;
	}
	Count[count]++;

	if (Count[5] == 1)
		return FiveKind;
	if (Count[4] == 1)
		return FourKind;
	if (Count[3] == 1) {
		if (Count[2] == 1)
			return FullHouse;
		else
			return ThreeKind;
	}
	if (Count[2] == 2)
		return TwoPair;
	if (Count[2] == 1)
		return OnePair;
	return HighCard;
}


type RateHand2(string h) {
	string s = h;
	int jokers = 0;
	sort(s.begin(), s.end());
	if (s[0] == 'J')
		jokers++;
	int Count[6];
	for (int i = 0; i < 6; i++)
		Count[i] = 0;
	int i = 1;
	int count = 1;
	char c = s[0];
	while (i < 5) {
		if (s[i] == 'J')
			jokers++;
		if (s[i] == c)
			count++;
		else {
			c = s[i];
			Count[count]++;
			count = 1;
		}
		i++;
	}
	Count[count]++;

	if (Count[5 - jokers] == 1 || jokers == 5)
		return FiveKind;
	if (Count[4] == 1 || (Count[3] == 1 && jokers == 1) || (Count[2] == 2 && jokers == 2) || jokers == 3)
		return FourKind;
	if (Count[3] == 1) {
		if (Count[2] == 1)
			return FullHouse;
		else
			return ThreeKind;
	}
	if (Count[2] == 2 && jokers == 1)
		return FullHouse;
	if (Count[2] == 1) {
		if (jokers >= 1)
			return ThreeKind;
		else
			return OnePair;
	}
	if (jokers == 2)
		return ThreeKind;
	if (Count[2] == 2)
		return TwoPair;
	if (jokers == 1)
		return OnePair;
	return HighCard;
}

struct less_than_hand
{
	inline bool operator() (const hand& h1, const hand& h2)
	{
		if (h1.t != h2.t)
			return (h1.t < h2.t);
		for (int i = 0; i < 5; i++) {
			if(h1.strength[i] != h2.strength[i])
				return (h1.strength[i] < h2.strength[i]);
		}
	}
};

struct less_than_hand2
{
	inline bool operator() (const hand& h1, const hand& h2)
	{
		if (h1.t2 != h2.t2)
			return (h1.t2 < h2.t2);
		for (int i = 0; i < 5; i++) {
			if (h1.strength2[i] != h2.strength2[i])
				return (h1.strength2[i] < h2.strength2[i]);
		}
	}
};

vector<hand> hands;

int main(int argc, char* argv[]) {
	long long total1 = 0;
	long long total2 = 0;
	string s;
	long long bid;
	ifstream f("data.txt");
	while (f >> s) {
		f >> bid;
		hand H = hand();
		H.bid = bid;
		for (int i = 0; i < 5; i++) {
			H.strength[i] = RateCard(s[i]);
			if (H.strength[i] == Jack)
				H.strength2[i] = Joker;
			else
				H.strength2[i] = H.strength[i];
		}
		H.t = RateHand(s);
		H.t2 = RateHand2(s);
		cout << s << ", " << H.t2 << endl;
		hands.push_back(H);
	}

	sort(hands.begin(), hands.end(), less_than_hand());
	for (int i = 0; i < hands.size(); i++) {
		total1 += hands[i].bid * (i + 1);
	}
	sort(hands.begin(), hands.end(), less_than_hand2());
	for (int i = 0; i < hands.size(); i++) {
		total2 += hands[i].bid * (i + 1);
	}


	cout << "The answer for part 1 is " << total1 << endl;
	cout << "The answer for part 2 is " << total2 << endl;
	return 0;
}