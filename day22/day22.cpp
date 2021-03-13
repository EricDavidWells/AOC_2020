#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <cstring>
#include "helper_functions.h"
#include <algorithm>

using namespace std;

class CardPool {
public:
	vector<int> cards;
};

class Deck {
public:
	deque<int*> cards;

	void display() {
		for (auto card : cards) {
			cout << *card << ",";
		}
		cout << endl;
	}
};

int main() {

	CardPool cardpool;
	cardpool.cards.reserve(100);
	Deck p1_deck;
	Deck p2_deck;

	string filename = "../../data/day22input.txt";
	ifstream file;
	file.open(filename);

	//int card_count = 0;
	if (file.is_open()) {
		string line;
		getline(file, line);
		while (getline(file, line)) {

			if (line == "") {
				break;
			}
			int card = stoi(line);
			cardpool.cards.push_back(card);
			//card_count++;
			p1_deck.cards.push_back(&cardpool.cards.at(cardpool.cards.size()-1));
		}
		getline(file, line);
		while (getline(file, line)) {
			int card = stoi(line);
			cardpool.cards.push_back(card);
			//card_count++;
			p2_deck.cards.push_back(&cardpool.cards.at(cardpool.cards.size()-1));
		}

		//cardpool.cards.erase(cardpool.cards.begin() + card_count, cardpool.cards.end());
	}
	else {
		return 1;
	}

	// part 1

	int turn_count = 0;
	while (p1_deck.cards.size() > 0 && p2_deck.cards.size() > 0) {

		/*cout << "p1_deck: ";
		p1_deck.display();
		cout << "p2_deck: ";
		p2_deck.display();*/

		int* p1_card = p1_deck.cards.front();
		int* p2_card = p2_deck.cards.front();

		p1_deck.cards.pop_front();
		p2_deck.cards.pop_front();

		if (*p1_card > *p2_card) {
			p1_deck.cards.push_back(p1_card);
			p1_deck.cards.push_back(p2_card);
		}
		else {
			p2_deck.cards.push_back(p2_card);
			p2_deck.cards.push_back(p1_card);
		}

		turn_count++;
	}

	cout << "p1 final deck: ";
	p1_deck.display();
	cout << "p2 final deck: ";
	p2_deck.display();

	long score = 0;
	for (int i = 0; i < cardpool.cards.size(); i++) {

		if (p1_deck.cards.size() > p2_deck.cards.size()) {
			score += (cardpool.cards.size()-i) * (*p1_deck.cards.at(i));
		}
		else {
			score += (cardpool.cards.size()-i) * (*p2_deck.cards.at(i));
		}
	}

	cout << "part 1 score: " << score << endl;
	return 0;
}