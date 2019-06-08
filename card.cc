#include <string>
#include <iostream>
#include "card.h"
using namespace std;


Card::Card(string num, string suit): num{num}, suit{suit}, isTrump{false},rank{-1}{}

void Card::calculateRank(const string &lead_suit, const string &trump_suit) {
    if (suit == trump_suit) {
        isTrump = true;
        if (num == "9") {
            rank = 7;
        }
        else if (num == "T") {
            rank = 8;
        }
        else if (num == "Q") {
            rank = 9;
        }
        else if (num == "K") {
            rank = 10;
        }
        else if (num == "A") {
            rank = 11;
        }
        else if (num == "J") {
            rank = 13;
        }
    }
    else if (suit == lead_suit) {
        if (num == "9") {
            rank = 1;
        }
        else if (num == "T") {
            rank = 2;
        }
        else if (num == "J") {
            if (trump_suit == "C" && lead_suit == "S") {
                rank = 12;
            }
            else if (trump_suit == "S" && lead_suit == "C") {
                rank = 12;
            }
            else if (trump_suit == "H" && lead_suit == "D") {
                rank = 12;
            }
            else if (trump_suit == "D" && lead_suit == "H") {
                rank = 12;
            }
            else {
                rank = 3;
            }
        }
        else if (num == "Q") {
            rank = 4;
        }
        else if (num == "K") {
            rank = 5;
        }
        else if (num == "A") {
            rank = 6;
        }
    }
    else {
        rank = 0;
    }
}


string Card::getSuit(){
	return suit;
}
string Card::getNum(){
	return num;
}
int Card::getRank(){
	return rank;
}
//int Card::getPlayer(){
//	return player;
//}
void Card::setRank(int r){
	rank = r;
}

string Card::display_card(){
	return (num + suit);
}

int Card::getisTrump() {
	return isTrump;
}

bool Card::equal(Card card1) {
	return ((card1.getSuit() == suit) && (card1.getNum() == num));
}

Card::~Card(){}

