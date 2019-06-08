//
// Created by Allen on 2018-11-21.
//

#ifndef EUCHRE_HAND_H
#define EUCHRE_HAND_H

#include <vector>
#include <iostream>
#include <memory>
#include "deck.h"
#include "card.h"

using namespace std;

//class Card;
//class Deck;
class Hand {
    vector<shared_ptr<Card>> hand;
    shared_ptr<Deck> deck;
    int numcards;
   public:
    Hand(shared_ptr<Deck> d);
    ~Hand();
    void removeCard(shared_ptr<Card> c);
    void addCard();
    bool isEmpty();
    string display_hand();
    string findMost();
    shared_ptr<Card> firstOk(const string &lead_suit, const string &trump_suit); //from Card*
    vector<shared_ptr<Card>> getHand();
    void setHand(vector<shared_ptr<Card>>);
    shared_ptr<Card> getfirst();
    //Hand* getHandPtr();
    void clear();
    //friend ostream& operator<<(ostream &out, const Hand &h);
};


#endif //EUCHRE_HAND_H

