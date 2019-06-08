#include "deck.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
using namespace std;


Deck::Deck() {}
Deck::~Deck() {}


void Deck::shuffle_cards(int seed) {
    back_to_original();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

void Deck::back_to_original() {
    vector<string> tmp;
    for (int i = 0; i < number_of_cards; ++i) {
        tmp.emplace_back(cards[i]);
    }
    for (int i = 0; i < number_of_cards; ++i) {
        cards[i] = cards_track[i];
    }
    for (int i = 0; i < number_of_cards; ++i) {
        cards_track[i] = tmp[i];
    }
}

string Deck::getTop() {
    string top = cards[0];
    cards.erase(cards.begin());
    cards.emplace_back(top);
    return top;
}

string Deck::indeck() {
    string re = "";
    int si = cards.size();
    for(int i=0;i<si;i++){
        re+=cards[i];
        if(i!=(si-1)){
            re+=" ";
        }
    }
    return re;
}

string Deck::restkitty(){
    string re = "";
    for(int i=0;i<3;i++){
        re+=cards[i];
        if(i!=2){
            re+=" ";
        }
    }
    return re;
}


