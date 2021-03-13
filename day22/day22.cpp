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
	vector<char> cards;
};

class Deck {
public:
	deque<char*> cards;

	void display() {
		for (auto card : cards) {
			cout << (int)*card << ",";
		}
		cout << endl;
	}
};

bool play_recursive_combat(Deck&, Deck&);
long count_score(Deck&);

int main() {

	CardPool cardpool;
	cardpool.cards.reserve(100);
	Deck p1_deck;
	Deck p2_deck;

	string filename = "../../data/day22input.txt";
	ifstream file;
	file.open(filename);

	if (file.is_open()) {
		string line;
		getline(file, line);
		while (getline(file, line)) {

			if (line == "") {
				break;
			}
			char card = stoi(line);
			cardpool.cards.push_back(card);
			p1_deck.cards.push_back(&cardpool.cards.at(cardpool.cards.size()-1));
		}
		getline(file, line);
		while (getline(file, line)) {
			char card = stoi(line);
			cardpool.cards.push_back(card);
			p2_deck.cards.push_back(&cardpool.cards.at(cardpool.cards.size()-1));
		}
	}
	else {
		return 1;
	}

	// part 1
	Deck p1_deck_pt1;
	copy(p1_deck.cards.begin(), p1_deck.cards.end(), back_inserter(p1_deck_pt1.cards));
	Deck p2_deck_pt1;
	copy(p2_deck.cards.begin(), p2_deck.cards.end(), back_inserter(p2_deck_pt1.cards));

	int turn_count = 0;
	while (p1_deck_pt1.cards.size() > 0 && p2_deck_pt1.cards.size() > 0) {

		char* p1_card = p1_deck_pt1.cards.front();
		char* p2_card = p2_deck_pt1.cards.front();

		p1_deck_pt1.cards.pop_front();
		p2_deck_pt1.cards.pop_front();

		if (*p1_card > *p2_card) {
			p1_deck_pt1.cards.push_back(p1_card);
			p1_deck_pt1.cards.push_back(p2_card);
		}
		else {
			p2_deck_pt1.cards.push_back(p2_card);
			p2_deck_pt1.cards.push_back(p1_card);
		}

		turn_count++;
	}

	cout << "p1 final deck: ";
	p1_deck_pt1.display();
	cout << "p2 final deck: ";
	p2_deck_pt1.display();

	bool winner = p1_deck_pt1.cards.size() > p2_deck_pt1.cards.size();
	long score;
	if (winner) {
		score = count_score(p1_deck_pt1);
	}
	else {
		score = count_score(p2_deck_pt1);
	}

	cout << "part 1 score: " << score << endl;

	// part 2

	Deck p1_deck_pt2;
	copy(p1_deck.cards.begin(), p1_deck.cards.end(), back_inserter(p1_deck_pt2.cards));
	Deck p2_deck_pt2;
	copy(p2_deck.cards.begin(), p2_deck.cards.end(), back_inserter(p2_deck_pt2.cards));

	winner = play_recursive_combat(p1_deck_pt2, p2_deck_pt2);

	cout << "p1 final deck: ";
	p1_deck_pt2.display();
	cout << "p2 final deck: ";
	p2_deck_pt2.display();

	if (winner) {
		score = count_score(p1_deck_pt2);
	}
	else {
		score = count_score(p2_deck_pt2);
	}
	cout << "part 2 score: " << score << endl;

	return 0;
}

// returns true for a player 1 win, false for a player 2 win
bool play_recursive_combat(Deck &p1_deck, Deck &p2_deck) {

	vector<Deck> p1_deck_history;
	vector<Deck> p2_deck_history;

	// loop while cards remain
	while (p1_deck.cards.size() > 0 && p2_deck.cards.size() > 0) {

		// check histories
		bool p1_history_flag = false;
		bool p2_history_flag = false;
		if (p1_deck_history.size() > 0) {
			for (Deck deck : p1_deck_history) {
				if (deck.cards == p1_deck.cards) {
					p1_history_flag = true;
					break;
				}
			}

			for (Deck deck : p2_deck_history) {
				if (deck.cards == p2_deck.cards) {
					p2_history_flag = true;
					break;
				}
			}

			if (p1_history_flag && p2_history_flag) {
				return true;
			}
		}
		
		p1_deck_history.push_back(p1_deck);
		p2_deck_history.push_back(p2_deck);

		char* p1_card = p1_deck.cards.front();
		char* p2_card = p2_deck.cards.front();

		p1_deck.cards.pop_front();
		p2_deck.cards.pop_front();

		bool winner;
		if (*p1_card > p1_deck.cards.size() || *p2_card > p2_deck.cards.size()) {
			// play normal game
			winner = *p1_card > *p2_card;
		}
		else {
			// play subgame

			Deck p1_subdeck;
			Deck p2_subdeck;
			copy(p1_deck.cards.begin(), p1_deck.cards.begin() + *p1_card, back_inserter(p1_subdeck.cards));
			copy(p2_deck.cards.begin(), p2_deck.cards.begin() + *p2_card, back_inserter(p2_subdeck.cards));

			winner = play_recursive_combat(p1_subdeck, p2_subdeck);
		}

		if (winner) {
			p1_deck.cards.push_back(p1_card);
			p1_deck.cards.push_back(p2_card);
		}
		else {
			p2_deck.cards.push_back(p2_card);
			p2_deck.cards.push_back(p1_card);
		}
	}

	return p1_deck.cards.size() != 0;
}

// counts score of deck
long count_score(Deck& deck) {
	long score = 0;
	int multiplier = deck.cards.size();
	for (char* val : deck.cards) {
		score += (multiplier) * (*val);
		multiplier--;
	}
	return score;
}