//
// Created by Allen on 2018-11-22.
//

#ifndef EUCHRE_PLAYER_H
#define EUCHRE_PLAYER_H

#include <iostream>
#include <memory>
#include "Hand.h"

//class Hand;
class Card;

class Player {
    bool isDealer;
    int score;
    int position;
    int partner;
    int wonTrick;
    int renegeCount;
    string trumpSuit;
    bool rage_quit;
  protected:
    bool goalone;
    //unique_ptr<Hand> phand;
  public:
    Player(int po, int pa); //po for position, pa for partner
    virtual bool decideTrump(const std::string &suitKitty)=0;
    virtual std::string pickTrump(const std::string &suitKitty)=0;
    virtual std::shared_ptr<Card> playCard(const std::string &lead_suit, const std::string &trump_suit, int opponent_score)=0;
    //virtual void display_player()=0;
    virtual ~Player()=0;
    virtual std::shared_ptr<Card> playfirst(const std::string &lead_suit, const std::string &trump_suit)=0;
    virtual void getCard()=0;
    void changeDealer();
    void setTrump(const std::string &s);
    bool getisDealer();
    std::string getTrump();
    int getPos();
    int getScore();
    int getTrick();
    int getRenegeCount();
    void addScore(int val);
    void addWonTrick();
    void addRenegeCount();
    void setScore(int val);
    void setTrick(int val);
    void setRenegeCount();
    virtual void goAlone()=0;
    virtual void clearhand()=0;
    virtual void orderup(std::string kitty)=0;
    bool getGoAlone();
    void setGoAlone();
    bool get_rage_quit();
    void set_rage_quit();
};


#endif //EUCHRE_PLAYER_H

