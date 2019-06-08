#include "ComputerPlayer.h"
#include "Hand.h"

using namespace std;

ComputerPlayer::ComputerPlayer(shared_ptr<Deck> d, int po, int pa,bool debugger,shared_ptr<Xwindow> xw): Player{po,pa}, phand{make_unique<Hand>(d)},
view{make_unique<MyDisplay>(debugger,xw)}{}

bool ComputerPlayer::decideTrump(const string &s) {
    string hand_to_display = phand->display_hand();
    view->computer_hand(hand_to_display,getPos(),getTrick());
    string s1 = phand->findMost();
    if(s==s1){
        return true;
    }
    else {
        return false;
    }
}

void ComputerPlayer::goAlone() {
    goalone = true;
}

string ComputerPlayer::pickTrump(const string &s) {
    string hand_to_display = phand->display_hand();
    view->computer_hand(hand_to_display,getPos(),getTrick());
    string s1 = phand->findMost();
    if(s1 == "pass"){
        return "p";
    }
    if(s1 != s){
        return s1;
    }
    else {
        return "p";
    }
}

shared_ptr<Card> ComputerPlayer::playCard(const string &lead_suit, const string &trump_suit, int opponent_score) {
    string hand_to_display = phand->display_hand();
    view->computer_hand(hand_to_display,getPos(),getTrick());
    shared_ptr<Card> c = phand->firstOk(lead_suit, trump_suit);
    view->card_played_in_response(c->getNum(), c->getSuit(),getPos());
    phand->removeCard(c);
    return c;
}

void ComputerPlayer::getCard(){
    phand->addCard();
}

ComputerPlayer::~ComputerPlayer(){}

shared_ptr<Card> ComputerPlayer::playfirst(const string &lead_suit, const string &trump_suit){
    string hand_to_display = phand->display_hand();
    view->computer_hand(hand_to_display,getPos(),getTrick());
    shared_ptr<Card> c = phand->getfirst();
    phand->removeCard(c);
    return c;
}

void ComputerPlayer::clearhand() {
    phand->clear();
}

void ComputerPlayer::orderup(string kitty) {
    string trump = "";
    string num = "";
    num += kitty[0];
    trump+=kitty[1];
    shared_ptr<Card> c1 = make_shared<Card>(num,trump);
    vector<shared_ptr<Card>> vc = phand->getHand();
    int size = vc.size();
    string hand_to_display = phand->display_hand();
    view->computer_hand(hand_to_display,getPos(),getTrick());
    for(int i=0; i<size; i++){
        if(vc[i]->getSuit() != trump || i==(size-1) ){
            string discarded = "";
            discarded += (vc[i]->getNum() + vc[i]->getSuit());
            vc[i] = c1;
            phand->setHand(vc);
            view->card_discarded(discarded);
            break;
        }
    }
}

