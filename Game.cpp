#include "Game.h"
#include "Player.h"
#include "card.h"
#include "deck.h"
#include "MyDisplay.h"
#include <time.h>
#include <cstdlib>
#include <sstream>
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

using namespace std;

Game::Game(Deck* de, MyDisplay* view,bool debugger,shared_ptr<Xwindow> xw0) : deck{std::shared_ptr<Deck>(de)},
    view{std::unique_ptr<MyDisplay>(view)}, trumpSuit{""}, leadSuit{""}, prevDealerPos{-1},
    currDealerPos{0}, nextDealerPos{-1}, goAlone{false},xw{xw0} {
    unique_ptr<Player> p0 = make_unique<HumanPlayer>(deck, 0, 2,debugger,xw0);
    unique_ptr<Player> p1 = make_unique<ComputerPlayer>(deck, 1, 3,debugger,xw0);
    unique_ptr<Player> p2 = make_unique<ComputerPlayer>(deck, 2, 0,debugger,xw0);
    unique_ptr<Player> p3 = make_unique<ComputerPlayer>(deck, 3, 1,debugger,xw0);
    //std::vector<std::unique_ptr<Player>> players (4, nullptr);
    players.emplace_back(move(p0));
    players.emplace_back(move(p1));
    players.emplace_back(move(p2));
    players.emplace_back(move(p3));
}

void Game::generate_random_dealer() {
     srand(time(NULL));
     int pos = (rand() % 4);
     currDealerPos = pos;
}

void Game::set_dealer() {
    players[currDealerPos]->changeDealer();
    int firstPos = 0;
    int lastPos = 3;
    if (currDealerPos == lastPos) {
        nextDealerPos = firstPos;
    } else {
        nextDealerPos = currDealerPos + 1;
    }
    
    if (prevDealerPos != -1) {
        players[prevDealerPos]->changeDealer();
    }
}


void Game::shuffle_cards(int seed) {
    string se = to_string(seed);
	istringstream convertstr{se};
    int n;
    convertstr >> n;
	deck->shuffle_cards(n);
	view->valueofseed(n);
	string content = deck->indeck();
	view->deckcontent(content);
}

void Game::distribute_cards() {
    int size = players.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 5 ; j++) {
			players[i]->getCard();
		}
	}
}


int Game::get_card(int num, const string &ls , const string &ts) {
    shared_ptr<Card> c = players[num]->playCard(ls, ts, players[1]->getScore());
    c->calculateRank(ls, ts);
    int re = c->getRank();
    return re;
}

int Game::gameplay(int first) {
	string player0_trick = to_string(players[0]->getTrick());
	string player1_trick = to_string(players[1]->getTrick());
	string player2_trick = to_string(players[2]->getTrick());
	string player3_trick = to_string(players[3]->getTrick());
	xw->drawString(220, 40, "trick: " + player0_trick, 3);
	xw->drawString(220, 430, "trick: " + player2_trick, 3);
	xw->drawString(20, 240, "trick: " + player3_trick, 6);
	xw->drawString(395, 240, "trick: " + player1_trick, 6);
	int size = players.size();
    int cards[size];
    view->trump_suit(trumpSuit); 
    for (int i = first; i < size+first; i++) {
        if(goAlone && i%4 == 2){
            //int fi = i%4;
            view->card_played_go_alone();
            shared_ptr<Card> th = players[2]->playfirst(leadSuit, trumpSuit);
            cards[2]=0;
        }else {
            int fi = i%4;
            if(i == first||((goAlone&& first%4 == 2)&& i ==(first+1))){
                shared_ptr<Card> th = players[fi]->playfirst(leadSuit, trumpSuit);
                leadSuit = th->getSuit();
                th->calculateRank(leadSuit, trumpSuit);
                int n = th->getRank();
                cards[fi]=n;
                view->lead_card(i,th->getNum(),th->getSuit());
                view->trump_suit(trumpSuit);
            }
            else {
                int n = get_card(fi, leadSuit, trumpSuit);
                cards[fi] = n;
            }
        }
    }
    int max = 0;
    for (int j = 0; j < size; j++){
        if (cards[j] > cards[max]) {
            max = j;
        }
    }
    players[max]->addWonTrick();
    view->trick_won(max);
    player0_trick = to_string(players[0]->getTrick());
	player1_trick = to_string(players[1]->getTrick());
	player2_trick = to_string(players[2]->getTrick());
	player3_trick = to_string(players[3]->getTrick());
	xw->drawString(220, 40, "trick: " + player0_trick, 1);
	xw->drawString(220, 430, "trick: " + player2_trick, 1);
	xw->drawString(20, 240, "trick: " + player3_trick, 1);
	xw->drawString(395, 240, "trick: " + player1_trick, 1);
    return max;
}


int Game::call_trump(){
    int score_t02 = players[0]->getScore();
    int score_t13 = players[1]->getScore();
    string st02 = to_string(score_t02);
    string st13 = to_string(score_t13);
    string kitty = deck->getTop();
    view->start_of_hand(st02,st13,kitty,currDealerPos);
    string rkitty = deck->restkitty();
    view->Rkitty(rkitty);
    string ksuit = "";
    ksuit += kitty[1];
    int playercalled;
    bool done = false;
    int size = players.size();
    for(int i=nextDealerPos;i<(size+nextDealerPos);i++){
        int fi = i%4;
        if(players[fi]->decideTrump(ksuit)){
            if(players[fi]->getGoAlone()){
                goAlone = true;
                players[fi]->setGoAlone();
            }
            done = true;
            playercalled = fi;
            trumpSuit = ksuit;
            view->player_order_kitty(fi);
            view->kitty_up();
            players[currDealerPos]->orderup(kitty);
            break;
        }
        view->player_pass_kitty(fi);
    }
    if(!done){
        view->kitty_down();
        string cu;
        for(int j=nextDealerPos;j<(size+nextDealerPos);j++){
            int fj = j%4;
            cu=players[fj]->pickTrump(ksuit);
            if(cu!="p"){
                if(players[fj]->getGoAlone()){
                goAlone = true;
                players[fj]->setGoAlone();
                 }
                trumpSuit = cu;
                playercalled = fj;
                done = true;
                view->player_declare_trump(fj,cu);
                break;
            }
            view->player_pass_trump(fj);
        }
    }
    if(!done){
        view->all_pass();
        return -1;
    }
    else{
        return playercalled;
    }
}

void Game::true_goAlone(){
    goAlone = true;
}


void Game::end_round(int playerCalled) {
	int team_tricks = players[0]->getTrick() + players[2]->getTrick();
	//int opponent_tricks = players[1]->getTrick() + players[3]->getTrick();	
    string player0_score = to_string(players[0]->getScore());
    string player1_score = to_string(players[1]->getScore());
	string player2_score = to_string(players[2]->getScore());
	string player3_score = to_string(players[3]->getScore());
	xw->drawString(220, 60, "score: " + player0_score, 3);
	xw->drawString(220, 450, "score: " + player2_score, 3);
	xw->drawString(20, 260, "score: " + player3_score, 6);
	xw->drawString(395, 260, "score: " + player1_score, 6);
	string player0_trick = to_string(players[0]->getTrick());
	string player1_trick = to_string(players[1]->getTrick());
	string player2_trick = to_string(players[2]->getTrick());
	string player3_trick = to_string(players[3]->getTrick());
	xw->drawString(220, 40, "trick: " + player0_trick, 3);
	xw->drawString(220, 430, "trick: " + player2_trick, 3);
	xw->drawString(20, 240, "trick: " + player3_trick, 6);
	xw->drawString(395, 240, "trick: " + player1_trick, 6);
	if (team_tricks == 0) {	
		players[1]->addScore(2);
		players[3]->addScore(2);
		if ((currDealerPos == 0) || (currDealerPos ==2)) {
			view->round_won_normal_team(1,3,0,2);
		} else {
			view->round_won_call_trump_team(1,3);
		}
	}
	else if (team_tricks == 1 || team_tricks == 2) {
		if (playerCalled == 0 || playerCalled == 2) {
			players[1]->addScore(2);
			players[3]->addScore(2);
		}
		else {
			players[1]->addScore(1);
			players[3]->addScore(1);
		}
		
		if ((currDealerPos == 0) || (currDealerPos ==2)) {
			    view->round_won_normal_team(1,3,0,2);
			} else {
			    view->round_won_call_trump_team(1,3);
			}
	}
	else if (team_tricks == 3 || team_tricks == 4) {
		if (playerCalled == 1 || playerCalled == 3) {
			players[0]->addScore(2);
			players[2]->addScore(2);
		}
		else {
			players[0]->addScore(1);
			players[2]->addScore(1);
		}
		
		if ((currDealerPos == 0) || (currDealerPos ==2)) {
			    view->round_won_call_trump_team(0,2);
		} else {
			    view->round_won_normal_team(0,2,1,3);
		}
	}
	else if (team_tricks == 5) {
		if (goAlone) {
			players[0]->addScore(4);
			players[2]->addScore(4);
			if ((currDealerPos == 0) || (currDealerPos ==2)) {
			    view->round_won_call_trump_team(0,2);
		    } else {
			    view->round_won_normal_team(0,2,1,3);
		    }
		}
		else {
			players[0]->addScore(2);
			players[2]->addScore(2);
			
			if ((currDealerPos == 0) || (currDealerPos ==2)) {
			    view->round_won_call_trump_team(0,2);
		    } else {
			    view->round_won_normal_team(0,2,1,3);
		    }
		}
	}
	players[0]->setTrick(0);
	players[1]->setTrick(0);
	players[2]->setTrick(0);
	players[3]->setTrick(0);
    players[0]->addScore((players[1]->getRenegeCount() + players[3]->getRenegeCount()) * 2);
    players[2]->addScore((players[1]->getRenegeCount() + players[3]->getRenegeCount()) * 2);
    players[1]->addScore((players[0]->getRenegeCount() + players[2]->getRenegeCount()) * 2);
    players[3]->addScore((players[0]->getRenegeCount() + players[2]->getRenegeCount()) * 2);
    player0_score = to_string(players[0]->getScore());
	player1_score = to_string(players[1]->getScore());
	player2_score = to_string(players[2]->getScore());
	player3_score = to_string(players[3]->getScore());
	xw->drawString(220, 60, "score: " + player0_score, 1);
	xw->drawString(220, 450, "score: " + player2_score, 1);
	xw->drawString(20, 260, "score: " + player3_score, 1);
	xw->drawString(395, 260, "score: " + player1_score, 1);
	players[0]->setRenegeCount();
    players[1]->setRenegeCount();
    players[2]->setRenegeCount();
    players[3]->setRenegeCount();
	goAlone = false;
	prevDealerPos = currDealerPos;
	currDealerPos = nextDealerPos;
}


bool Game::end_game() {
    if (players[0]->getScore() >= 10 && players[0]->get_rage_quit() == true) {
        view->team_won(0,2);
        throw 0;
    }
    else if (players[1]->getScore() >= 10 && players[0]->get_rage_quit() == true) {
        view->team_won(1,3);
        throw 0;
    }
    else if (players[0]->getScore() >= 10 && players[1]->getScore() >= 10) {
        view->team_won(1,3);
        return true;
    }
    else if (players[0]->getScore() >= 10) {
        view->team_won(0,2);
		return true;
	}
	else if (players[1]->getScore() >= 10) {
	    view->team_won(1,3);
		return true;
	}
    return false;
}

Game::~Game(){}

void Game::clear_everyone() {
    for(int i=0; i< 4; i++){
        players[i]->clearhand();
    }
}

