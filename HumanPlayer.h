#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_
#include <string>
#include <memory>
#include <vector>
#include "Player.h"
#include "MyDisplay.h"


class HumanPlayer: public Player {
    std::unique_ptr <Hand> phand;
	std::string play_suit;
    std::unique_ptr <MyDisplay> view;
public:
	HumanPlayer(std::shared_ptr<Deck> d, int po, int pa,bool debugger,std::shared_ptr<Xwindow> xw);
	bool decideTrump(const std::string &suitKitty) override;
    std::string pickTrump(const std::string &suitKitty) override;
	std::shared_ptr<Card> playCard(const std::string &lead_suit, const std::string &trump_suit, int opponent_score) override;
	std::shared_ptr<Card> playfirst(const std::string &lead_suit, const std::string &trump_suit) override;
	bool renege(const std::string &lead_suit, vector<std::shared_ptr<Card>> hand, std::shared_ptr<Card> card);
	void goAlone() override;
	void getCard() override;
    std::string get_play_suit();
    ~HumanPlayer() override;
	void clearhand() override;
	void orderup(std::string kitty) override;
    //std::unique_ptr<Hand> get_phand();
};


#endif

