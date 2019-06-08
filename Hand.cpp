#ifndef _Hand_CPP_
#define _Hand_CPP_
#include "Hand.h"
#include "card.h"

using namespace std;

vector<shared_ptr<Card>> Hand::getHand() {
    return hand;
}
void Hand::setHand(vector<shared_ptr<Card>> h) {
    hand = h;
}

Hand::Hand(shared_ptr<Deck> d):deck(d),numcards{0}{
}

Hand::~Hand(){
    for(int i=0; i<numcards; i++) {
        hand.pop_back();
    }
}

//Hand* Hand::getHandPtr(){
//    return this;
//}

void Hand::removeCard(shared_ptr<Card> c){
    int mark=0;
    //int cr;
    if(numcards!=0){
      for(int i=0;i<numcards;i++){
          if(hand[i]->equal(*c)){
              mark = i;
              break;
          }
      }
      hand.erase(hand.begin()+mark);
      numcards--;
    }
}

void Hand::addCard(){
    string top = deck->getTop();
    string num = top.substr(0, 1);
    string suit = top.substr(1, 1);
    shared_ptr<Card> new_card = make_shared<Card>(num, suit);
    hand.emplace_back(new_card);
    numcards++;
}

bool Hand::isEmpty(){
    if(numcards==0){
       return true;
    }else {
        return false;
    }
}
string Hand::display_hand(){
    string cards = " ";
    for(int i=0; i < numcards; i++){
        cards = cards + hand[i]->display_card() + " ";
    }
    return cards;
}

string Hand::findMost() {
    int f[4]{0, 0, 0, 0};
    int maxp;
    for(int i=0; i<numcards;i++){
        if(hand[i]->getSuit()=="D"){ f[0] = f[0] + 1;}
        else if(hand[i]->getSuit()=="C"){f[1] = f[1] + 1;}
        else if(hand[i]->getSuit()=="H"){f[2] = f[2] + 1;}
        else{f[3] = f[3] + 1;}
    }
    int max=f[0];
    for(int j=0; j<4; j++){
        if(f[j]>max){
            max = f[j];
            maxp = j;
        }
    }
    if(max < 4){return "pass";}
    if(maxp==0){return "D";}
    else if(maxp==1){return "C";}
    else if(maxp==2){return "H";}
    else{return "S";}
}

shared_ptr<Card> Hand::firstOk(const string &lead_suit, const string &trump_suit){
    for(int i=0; i<numcards; ++i) {
        string ha =  hand[i]->getSuit();
        if (hand[i]->getSuit() == lead_suit) {
            return hand[i];
        }
    }
    for(int i=0; i<numcards; ++i) {
        if (hand[i]->getSuit() == trump_suit) {
            return hand[i];
        }
    }
    return hand[0];
}

shared_ptr<Card> Hand::getfirst(){
    return hand[0];
}

void Hand::clear(){
    for(int j = 0; j<5;j++){
        hand.erase(hand.begin());
        numcards--;
    }
}

#endif

