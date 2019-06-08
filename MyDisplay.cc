#include <string>
#include <iostream>
#include "MyDisplay.h"

using namespace std;

MyDisplay::MyDisplay(bool debugger,shared_ptr<Xwindow> xw0):MyDebugger{debugger},xw{xw0}{
};

void MyDisplay::welcome_message() {
    cout << "Welcome to Euchre" << endl;
    cout << endl;
    cout << "You are Play 0" << endl;
    cout << endl;
    cout << "Please enter 'q' whenever you would like to quit the game" << endl;
    cout << endl;
    cout << "Enjoy the game" << endl;
    cout << endl;
}

void MyDisplay::quit_message() {
    cout << "Player 0 rage quit " << endl;
    cout << endl;     
}

void MyDisplay::discard_one_card() {
    cout << "Please select a card to swap for the top card of kitty or enter 'p' to pass" << endl;
    cout << endl;
    cout << "> ";
}

void MyDisplay::trump_suit(string trumpsuit) {
    xw->fillRectangle(20,70,150,25,0);
    xw->fillRectangle(124,0,10,10,0);
    xw->drawBigString(125,10,trumpsuit);
    cout << "The trump suit is " << trumpsuit << endl;
    cout << endl;
}

void MyDisplay::decide_trump() {
    cout << "Please enter 'p' if you decline the top kitty as trump suit." << endl;
    cout << endl;
    cout << "Otherwise, enter 'o' if you would like to order up the kitty and enter 'a' if you would like to go alone as well (eg.'oa')" << endl;
    cout << endl;
    cout << "> ";
}

void MyDisplay::play_card() {
    cout << "Please choose one card" << endl;
    cout << endl;
    cout << "> ";
}
void MyDisplay::lead_suit(string suit) {
   cout << "The lead suit is " << suit << endl;
}
void MyDisplay::trump_suit_txt(string suit) {
    cout << "The trump suit is " << suit << endl;
}
void MyDisplay::order_trump_suit () {
    cout << "Please enter a trump suit that you would like to order and a n if you don't want to go alone or a a for othterwise(eg 'H n', 'H a')" << endl;
    cout << endl;
    cout << "> ";
}

void MyDisplay::your_hand(string card,int wontrick,bool ifplay) {
    cout << "You have" << card << "in your hand" << endl;
    cout << endl;
    if(MyDebugger){
        if(wontrick<2){
            cout<<"You have won "<< wontrick << " trick"<< endl;
            cout << endl;
        }
        else{
            cout<<"You have won "<< wontrick << " tricks"<< endl;
            cout << endl;
        }
    }
    if(ifplay){
       cout << "Please choose one card to play" << endl;
       cout << endl;
       cout << "> ";
    }
}

void MyDisplay::your_hand_discard(string card) {
    cout << "You have" << card << "in your hand " << endl;
    cout << endl;
}

void MyDisplay::computer_hand(string card,int pos,int wontrick) {
    if(MyDebugger){
        cout << "Player " << pos << " has" << card << "in the hand" << endl;
        cout << endl;
        if(wontrick < 2){
            cout<< "Player " << pos <<  " have won "<< wontrick << " trick" << endl;
            cout << endl;
        }
        else{
            cout<< "Player " << pos <<  " have won "<< wontrick << " tricks" << endl;
            cout << endl;
        }
    }
}

void MyDisplay::start_of_hand (string score0, string score1, string topkitty, int player_start_trump ){
	cout << "Team 0-2 has score: " << score0 << endl;
    cout << endl;
	cout << "Team 1-3 has score: " << score1 << endl;
    cout << endl;
	cout << "The top card of the kitty: " << topkitty << endl;
	string kitty1 = "Top card of the kitty: "+ topkitty;
	xw->fillRectangle(124,0,10,10,0);
	xw->fillRectangle(138,36,10,18,0);
	xw->fillRectangle(20,70,150,25,0);
	xw->drawBigString(20,90,kitty1);
    cout << endl;
	cout << "Player " << player_start_trump <<" is the dealer and starts the decision-making on trump" << endl;
	if(player_start_trump==0){
	     xw->fillRectangle(118,292,37,13,0);
	     xw->drawBigString(200,122,"Dealer",2);
	}
	else if(player_start_trump==1){
	               xw->fillRectangle(200,112,35,12,0);
	               xw->drawBigString(390,312,"Dealer",2);
	}
	else if(player_start_trump==2){
	     xw->fillRectangle(390,302,35,12,0);
	     xw->drawBigString(200,385,"Dealer",2);
	}
	else{
	    xw->fillRectangle(200,376,35,13,0);
	    xw->drawBigString(117,302,"Dealer",2);
	}
    cout << endl;
}

void MyDisplay::player_pass_kitty (int name) {
	cout << "Player " << name << " decides to pass the top card of the kitty" << endl;
    cout << endl;
}
void MyDisplay::player_order_kitty(int name) {
	cout << "Player " << name << " decides to order the top card of the kitty" << endl;
    cout << endl;
}

void MyDisplay::kitty_down () {
	cout << "The top card of the kitty is turned down" << endl;
    cout << endl;
}
void MyDisplay::kitty_up (){
	cout << "The top card of the kitty is still facing up" << endl;
    cout << endl;
}

void MyDisplay::player_pass_trump (int name) {
	cout << "Player " << name << " decides to pass" << endl;
    cout << endl;
}

void MyDisplay::player_declare_trump(int name, string suit) {
	cout << "Player " << name << " decides to declare " << suit << " as the trump suit" << endl;
    cout << endl;
}

void MyDisplay::all_pass(){
	cout << "All players pass and hands are disgarded" << endl;
    cout << endl;
}

void MyDisplay::card_played_in_response(string num, string suit,int name) {
	cout << num << suit  << " is played by Player " << name << " in response" << endl;
	string played0 = "Player 0 played " + num + suit;
	string played1 = "Player 1 played " + num + suit;
	string played2 = "Player 2 played " + num + suit;
    string played3 = "Player 3 played " + num + suit;
	if(name == 0){
	    xw->drawBigString(215,235,played0);
	}
	else if(name == 1){
        xw->drawBigString(215,260,played1);
    }
    else if(name == 2){
        xw->drawBigString(215,285,played2);
    }
    else{
        xw->drawBigString(215,310,played3);
    }
    cout << endl;
}

void MyDisplay::card_played_go_alone() {
	cout << "Player 2 skipped since Player 0 goes alone" << endl;
    cout << endl;
}


void MyDisplay::lead_card(int name, string num, string suit) {
    cout << "Player " << name << " goes first and the card is " << num << suit << endl;
    cout << "The leading suit is " << suit << endl;
    xw->fillRectangle(138,36,10,18,0);
    xw->drawBigString(143,50,suit);
    cout << endl;
    string played0 = "Player 0 played " + num + suit;
    string played1 = "Player 1 played " + num + suit;
    string played2 = "Player 2 played " + num + suit;
    string played3 = "Player 3 played " + num + suit;
    if(name == 0){
        xw->drawBigString(215,235,played0);
    }
    else if(name== 1){
        xw->drawBigString(215,260,played1);
    }
    else if(name == 2){
        xw->drawBigString(215,285,played2);
    }
    else{
        xw->drawBigString(215,310,played3);
    }
}

void MyDisplay::player_renege(int score02, int score13) {
	cout << "You choose to renege" << endl;
    cout << endl;
	cout << "The score of Team 0-2 is " << score02 << endl;
    cout << endl;
	cout << "The new score of Team 1-3 is " << score13 << endl;
    cout << endl;
}

void MyDisplay::re_enter_valid_card() {
	 cout << "You picked a card that is not in your hand, please re-enter a valid card" << endl;
	 cout << endl;
     cout << "> ";
}
void MyDisplay::re_enter_valid_card_renege() {
	cout << "Please re-enter a valid card:" << endl;
    cout << endl;
    cout << "> ";
}

void MyDisplay::trick_won(int name) {
	cout << "Player " << name << " took the trick" << endl;
    cout << endl;
    xw->fillRectangle(210,225,123,120,0);
}

void MyDisplay::round_won_call_trump_team(int name1, int name2) {
	cout << "The hand has been played" << endl;
    cout << endl;
	cout << "Team " << name1 << "-" << name2 << " won the hand"  << endl;
    cout << endl;
	cout << "Team " << name1 << "-" << name2 << " is not euchred" << endl;
    cout << endl;
}

void MyDisplay::round_won_normal_team(int name1, int name2, int name3, int name4) {
	cout << "The hand has been played" << endl;
    cout << endl;
    cout << "Team " << name1 << "-" << name2 << " won the hand"  << endl;
    cout << endl;
	cout << "Team " << name3 << "-" << name4 << " is euchred" << endl;
    cout << endl;
}


void MyDisplay::team_won(int name1, int name2) {
	cout << "Team " << name1 << "-" << name2 << " won the game" << endl;
    cout << endl;
}

void MyDisplay::select_trump_not_valid() {
	cout << "Sorry, you could not select the same suit again. Please enter a new trump suit:" << endl;
	cout << endl;
    cout << "> ";
}

void MyDisplay::display_replay(){
    cout<<"Great game! Do you want to another game?"<<endl;
    cout<<"Please input Yes for replay; No for exit"<<endl;
    cout << endl;
    cout << "> ";
}

void MyDisplay::display_thanks(){
    cout<<"Thanks for playing! Have a great day!"<<endl;
}

void MyDisplay::ask_for_num() {
    cout <<"Invalid input Please enter a number" << endl;
    cout << "> ";
}

void MyDisplay::anothergame(){
	cout<<"New game has started Please enter a number to shuffle" << endl;
}
void MyDisplay::invalidinput(){
    cout << "Invalid input Please try again" <<endl;
    cout << endl;
    cout << "> ";
}


void MyDisplay::setMydebugger(){
    MyDebugger = true;
}

void MyDisplay::valueofseed(int n){
	if(MyDebugger){
		cout << "the value of seed is " << n <<endl;
        cout << endl;
	}
}

void MyDisplay::card_discarded(std::string s){
    if(MyDebugger){
        cout << "the card discarded is " << s <<endl;
        cout << endl;
    }
}

void MyDisplay::deckcontent(std::string content) {
    if(MyDebugger){
        cout<<"the order of the deck: " << content << endl;
        cout << endl;
    }
}

void MyDisplay::Rkitty(std::string content){
    if(MyDebugger){
        cout<<"the rest of kitty: "<< content << endl;
        cout << endl;
    }
}

void MyDisplay::cleanleads(){
   xw->fillRectangle(138,36,10,18,0);
}

