#ifndef _Display_H
#define _Display_H
#include <string>
#include <iostream>
#include "window.h"
#include <memory>

class MyDisplay {
    bool MyDebugger;
    std::shared_ptr<Xwindow> xw;
public:
    MyDisplay(bool debugger,std::shared_ptr<Xwindow> xw0);
    void welcome_message();

    void quit_message();
    void lead_suit(std::string suit);
    void trump_suit_txt(std::string suit);

    void discard_one_card();

    void start_of_hand(std::string score0, std::string score1, std::string topkitty, int player_start_trump);

    void player_pass_kitty(int name);

    void player_order_kitty(int name);

    void computer_hand(std::string card, int pos, int wontrick);

    void trump_suit(std::string trumpsuit);

    void kitty_down();

    void kitty_up();

    void decide_trump();

    void order_trump_suit();

    void player_pass_trump(int name);

    void player_declare_trump(int name, std::string suit);

    void all_pass();

    void card_played_in_response(std::string num, std::string suit, int name);

    void card_played_go_alone();

    void lead_card(int name, std::string num, std::string suit);

    void player_renege(int score02, int score13);

    void re_enter_valid_card();

    void re_enter_valid_card_renege();

    void trick_won(int name);

    void round_won_call_trump_team(int name1, int name2);

    void round_won_normal_team(int name1, int name2, int name3, int name4);

    void team_won(int name1, int name2);

    void select_trump_not_valid();

    void display_replay();

    void display_thanks();

    void choose_to_go_alone();

    void your_hand(std::string card, int wontrick,bool ifplay);

    void your_hand_discard(std::string card);

    void play_card();

    void ask_for_num();

    void anothergame();

    void invalidinput();

    void setMydebugger();

    void valueofseed(int n);

    void card_discarded(std::string s);

    void deckcontent(std::string content);

    void Rkitty(std::string content);
    //void lead_suit(std string suit);

    void cleanleads();
};
#endif

