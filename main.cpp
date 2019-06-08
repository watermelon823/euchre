#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>
#include <string>
#include "card.h"
#include "deck.h"
#include "Player.h"
#include "Game.h"
#include "MyDisplay.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "window.h"
using namespace std;

int main(int argc, char* argv[]){
    ifstream inputfile;
    std::shared_ptr<Xwindow> xw0 = make_shared<Xwindow>();
    xw0->fillRectangle(200,10,100,100,3);
    xw0->fillRectangle(200,390,100,100,3);
    xw0->fillRectangle(10,200,100,100,6);
    xw0->fillRectangle(390,200,100,100,6);
    xw0->drawString(220, 20, "player 0", 1);
    xw0->drawString(220, 410, "player 2", 1);
    xw0->drawString(20, 220, "player 3", 1);
    xw0->drawString(395, 220, "player 1", 1);
    xw0->fillRectangle(118,292,37,13,0);
    xw0->fillRectangle(200,112,35,12,0);
    xw0->fillRectangle(390,302,35,12,0);
    xw0->fillRectangle(200,376,35,13,0);
    xw0->drawBigString(20,10,"Current TrumpSuit:");
    xw0->drawBigString(20,50,"Current LeadingSuit: ");
    //streambuf* orig_cin = cin.rdbuf();
	int round = 0;
    bool flag = false;
    for (int i = 0; i < argc; i++){
        string com = argv[i];
        if (com == "-f") {
          inputfile.open(argv[i+1]);
          cin.rdbuf(inputfile.rdbuf());
          flag = true;
          break;
        }
    }
    int seed = 0;
    bool input_seed = false;
    for (int i = 0; i < argc; i++) {
        string input = argv[i];
        if ((input == "-s") && (flag == false)) {
            string input = argv[i + 1];
            istringstream ss{input};
            ss >> seed;
            input_seed = true;
        } else if (input == "-s") {
            cin >> seed;
            input_seed = true;
        
			}
		}
	if (input_seed == false && flag == true) {
			cin >> seed;
			input_seed = true;
	}
    bool quit = false;
    bool endgame = false;
    bool debugger = false;
    for (int i = 0; i < argc; i++) {
        string input = argv[i];
        if (input == "-d") {
            debugger = true;
        }
    }
    std::unique_ptr<MyDisplay> view (new MyDisplay(debugger,xw0));
    view->welcome_message();
    try {
    while(!quit) {
        Deck *d = new Deck();
        MyDisplay *v = new MyDisplay(debugger,xw0);
        Game g1(d, v,debugger,xw0);
        int first=1;
        string str;
        if (input_seed == true) {
            g1.shuffle_cards(seed);
        }
        else {
            g1.shuffle_cards(0);
        }
        while(!endgame){
            //g1.generate_random_dealer();
                g1.set_dealer();
				if (round != 0) {
                	g1.shuffle_cards(seed);
				}
				round++;
                seed = seed + 2;
                g1.distribute_cards();
                int endnow = g1.call_trump();
                if(endnow == -1){
                    g1.clear_everyone();
                    continue;
                }
                for(int i = 0;i<5;i++){
                   first = g1.gameplay(first);
                }
            g1.end_round(endnow);
            endgame = g1.end_game();
			if (endgame == true) {
				round = 0;
			}
        }
        view->display_replay();
        string s;
        while(s!="Yes" && s!="No"){
            cin>>s;
            if(s!="Yes" && s!="No"){
                view->invalidinput();
            }
        }
        if(s=="Yes"){
            endgame=false;
            view->anothergame();
        }
        else{
            view->display_thanks();
            quit = true;
        }
        }
    }
    catch (int &e) {
        return 0;
    }
}

