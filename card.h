# ifndef _CARD_H_
# define _CARD_H_
#include <string>
#include <iostream>

class Card {
	std::string num;
	std::string suit;
	//int player;
	bool isTrump;
	int rank;
	//const int default_val = 0;

public:
	Card(std::string num, std::string suit);
    void calculateRank(const std::string &lead_suit, const std::string &trump_suit);
	bool equal(Card card1);
	std::string getSuit();
	std::string getNum();
	int getRank();
	//int getPlayer();
	int getisTrump();
	void setRank(int r);
	std::string display_card();
	~Card();
};


#endif

