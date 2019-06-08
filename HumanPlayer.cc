#include "HumanPlayer.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;	

void HumanPlayer::orderup(string kitty) {
    bool isvalid = false;
    string trump = "";
    string num = "";
    trump += kitty[1];
    num += kitty[0];
    shared_ptr<Card> c = make_shared <Card>(num, trump);
	string hand_to_display = phand->display_hand();
    //view->your_hand_discard(hand_to_display);
    vector<shared_ptr<Card>> v = phand->getHand();
    int wontrick = getTrick();
    view->your_hand(hand_to_display, wontrick,false);
    view->discard_one_card();
    int size = v.size();
    if (get_rage_quit() == true) {
        for (int i = 0; i < size; i++) {
            if (v[i]->getSuit() != trump || i == (size - 1)) {
                v[i] = c;
                phand->setHand(v);
                isvalid = true;
                break;
            }
        }
    }
    else {
	    string s;
	    while (cin >> s) {
            if (s == "q") {
                throw 0;
        }
        if (s == "r") {
            set_rage_quit();
            for (int i = 0; i < size; i++) {
                if (v[i]->getSuit() != trump || i == (size - 1)) {
                    v[i] = c;
                    phand->setHand(v);
                    isvalid = true;
                    break;
                }
            }
        }
        string num_to_discard = "";
        num_to_discard += s[0];
        string suit_to_discard = "";
        suit_to_discard += s[1]; 
        if (s == "p") {
            isvalid = true;
            break;
        }
	    for (int i = 0; i < size; i++) {
	        if ((v[i]->getNum() == num_to_discard) && (v[i]->getSuit() == suit_to_discard)) {
	            v[i] = c;
	            phand->setHand(v);
	            view->card_discarded(s);
	            isvalid = true;
	            break;
	        }
	    }
	    if (isvalid == true) {
	        break;
	    } 
        else {
          view->invalidinput();
	        continue;
	        }
        }
	}
}

void HumanPlayer::getCard() {
    phand->addCard();
}


string HumanPlayer::get_play_suit() {
    return play_suit;
}

HumanPlayer::HumanPlayer(shared_ptr<Deck>d,int po, int pa,bool debugger,std::shared_ptr<Xwindow> xw) : Player{po,pa},phand{make_unique<Hand>(d)},
play_suit{""}, view{make_unique<MyDisplay>(debugger,xw)} {}

bool HumanPlayer::decideTrump(const string &suitKitty) {
    string hand_to_display = phand->display_hand();
    int wontrick = getTrick();
    view->your_hand(hand_to_display, wontrick,false);
    view->decide_trump();
    if (get_rage_quit() == true) {
        string s = phand->findMost();
        if (s == suitKitty) {
            return true;
        }
        else {
            return false;
        }
    }
	string decision;
	cin>>decision;
	//getline(cin,decision);
	while(decision!="r" && decision!="q" && decision!="p" && decision!="oa" && decision !="o"){
	    view->invalidinput();
        cin>>decision;
	}
    if (decision == "r") {
        set_rage_quit();
        string s = phand->findMost();
        if (s == suitKitty) {
            return true;
        }
        else {
            return false;
        }
    }
    if (decision == "q") {
        throw 0;
    }
    string d = "";
    d += decision[0];
    if (decision.length() == 2) {
        goAlone();
    }
	if (decision == "p") {
		return false;
	} else {
		return true;
	}
}

string HumanPlayer::pickTrump(const string &trump_suitKitty) {
    string hand_to_display = phand->display_hand();
    int wontrick = getTrick();
    view->your_hand(hand_to_display, wontrick,false);
    view->order_trump_suit();
    if (get_rage_quit() == true) {
        string s = phand->findMost();
        if (s == trump_suitKitty) {
            return s;
        }
        else {
            return "p";
        }
    }
    string decision;
    cin>>decision;
    while(decision!="D" && decision!="C" && decision!="H" && decision!="S" && decision!="r" && decision != "p"
          && decision != "q"){
        view->invalidinput();
        string out;
        cin>>out;
        cin>>decision;
    }
    if(decision == "D" ||decision =="C" || decision =="H" || decision =="S"){
        string n_a;
        cin >> n_a;
        while(n_a!="n" && n_a!="a"){
            view->invalidinput();
            cin>>decision;
            while(decision!="D" && decision!="C" && decision!="H" && decision!="S" && decision!="r" && decision != "p"
                  && decision != "q"){
                view->invalidinput();
                string out;
                cin >> out;
                cin>>decision;
            }
            cin>>n_a;
        }
        if (n_a == "a") {
            goAlone();
        }
    }
    if (decision == "r") {
        set_rage_quit();
        string s = phand->findMost();
        if (s == trump_suitKitty) {
            return s;
        }
        else {
            return "p";
        }
    }
    if (decision == "q") {
        throw 0;
    }
	while (decision == trump_suitKitty) {
        view->select_trump_not_valid();
        cin >> decision;
        if (decision == "q") {
            throw 0;
        }
    }
	return decision;
}

shared_ptr<Card> HumanPlayer::playfirst(const string &lead_suit, const string &trump_suit) {
    bool valid = false;
    string card_name;
    string hand_to_display = phand->display_hand();
    int wontrick = getTrick();
    //view->lead_suit(lead_suit);
    view->trump_suit_txt(trump_suit);
    view->your_hand(hand_to_display, wontrick,false);
    view->cleanleads();
    view->play_card();
    if (get_rage_quit() == true) {
        shared_ptr<Card> c = phand->getfirst();
        phand->removeCard(c);
        return c;
    }
    cin >> card_name;
    if (card_name == "r") {
        set_rage_quit();
        shared_ptr<Card> c = phand->getfirst();
        phand->removeCard(c);
        return c;
    }
    if (card_name == "q") {
        throw 0;
    }
    vector<shared_ptr<Card>> hand = phand->getHand();
    shared_ptr<Card>card_played = hand.at(0);
    int size = hand.size();
    while (valid == false) {
        for (int i = 0; i < size; i++) {
            if (card_name == hand[i]->getNum() + hand[i]->getSuit()) {
                card_played = hand.at(i);
                valid = true;
            }
        }
        if (valid == false) {
            view->your_hand(hand_to_display, wontrick,false);
            view->re_enter_valid_card();
            cin >> card_name;
            if (card_name == "q") {
               throw 0;
            }
        }
    }
    phand->removeCard(card_played);
    return card_played;
}

shared_ptr<Card> HumanPlayer::playCard(const string &lead_suit, const string &trump_suit, int opponent_score) {
	string card_name;
    bool valid_card = false;
    bool valid_play = false;
    vector<shared_ptr<Card>> hand = phand->getHand();
    shared_ptr<Card> card_played = hand.at(0);
    int size = hand.size();
    string hand_to_display = phand->display_hand();
    view->lead_suit(lead_suit);
    view->trump_suit_txt(trump_suit);
    view->your_hand(hand_to_display, getTrick(),true);
    if (get_rage_quit() == true) {
        auto c = phand->firstOk(lead_suit, trump_suit);
        phand->removeCard(c);
        return c;
    }
    cin >> card_name;
    if (card_name == "r") {
        set_rage_quit();
        auto c = phand->firstOk(lead_suit, trump_suit);
        phand->removeCard(c);
        return c;
    }
    if (card_name == "q") {
        throw 0;
    }
    while (valid_play == false) {
        valid_card = false;
        for (int i = 0; i < size; ++i) {
            if (card_name == hand[i]->getNum() + hand[i]->getSuit()) {
                card_played = hand.at(i);
                if (renege(lead_suit, hand, card_played) == false) {
                    play_suit = card_played->getSuit();
                    valid_card = true;
                    valid_play = true;
                }
                else if (renege(lead_suit, hand, card_played) == true) {
                    addRenegeCount();
                    valid_card = true;
                    int oppscore =  opponent_score + getRenegeCount() * 2;
                    view->player_renege(getScore(), oppscore);
					if (oppscore >= 10) {
						view->team_won(1, 3);
						throw 0;
					}
                    view->your_hand(hand_to_display,getTrick(),false);
                    view->re_enter_valid_card_renege();
                    cin >> card_name;
                    if (card_name == "q") {
                        throw 0;
                    }
                }
            }
        }
        if (valid_card == false) {
            view->your_hand(hand_to_display,getTrick(),false);
            view->re_enter_valid_card();
            cin >> card_name;
            if (card_name == "q") {
              throw 0;
            }
        }
    }
    view->card_played_in_response(card_played->getNum(), card_played->getSuit(),getPos());
    phand->removeCard(card_played);
    return card_played;
}


bool HumanPlayer::renege(const string &lead_suit, vector<shared_ptr<Card>> hand, shared_ptr<Card> card) {
    int lead_count = 0;
	int size = hand.size();
    for (int i = 0; i < size; ++i) {
        if (hand[i]->getSuit() == lead_suit) {
            lead_count++;
        }
    }
    if (lead_count != 0) {
        if (card->getSuit() != lead_suit) {
            return true;
        }
    }
    return false;
}


void HumanPlayer::goAlone() {
    goalone = true;
}

HumanPlayer::~HumanPlayer(){}

void HumanPlayer::clearhand() {
    phand->clear();
}


