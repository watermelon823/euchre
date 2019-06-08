//
// Created by Allen on 2018-11-22.
//

#ifndef EUCHRE_COMPUTERPLAYER_H
#define EUCHRE_COMPUTERPLAYER_H

#include "Player.h"
#include "MyDisplay.h"

class Deck;

class ComputerPlayer: public Player {
    std::unique_ptr<Hand> phand;
    std::unique_ptr <MyDisplay> view;
  public:
    ComputerPlayer(std::shared_ptr<Deck> d,int po, int pa,bool debugger,std::shared_ptr<Xwindow> xw);
    bool decideTrump(const std::string &suitkitty) override;
    string pickTrump(const std::string &suitkitty) override;
    shared_ptr<Card> playCard(const std::string &lead_suit, const std::string &trump_suit, int opponent_score) override;
    //void display_player() override;
    shared_ptr <Card> playfirst(const std::string &lead_suit, const std::string &trump_suit) override;
    void getCard() override;
    void goAlone() override;
    ~ComputerPlayer() override;
    void clearhand() override;
    void orderup(std::string kitty) override;
};


#endif //EUCHRE_COMPUTERPLAYER_H

