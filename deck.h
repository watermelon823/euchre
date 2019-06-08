#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include <string>

class Deck {
    std::vector<std::string> cards = {"AS", "QC", "KC", "KS", "JS", "9D", "TS", "9S", "JH", "JD", "AH", "9H", 
        "AD", "QS", "TC", "AC", "KD", "9C", "TD", "QH", "QD", "TH", "KH", "JC"};
    std::vector<std::string> cards_track = {"AS", "QC", "KC", "KS", "JS", "9D", "TS", "9S", "JH", "JD", "AH", "9H",
        "AD", "QS", "TC", "AC", "KD", "9C", "TD", "QH", "QD", "TH", "KH", "JC"};
    const int number_of_cards = 24;

public:
    Deck();
    ~Deck();
    void shuffle_cards(int seed);
    void back_to_original();
    std::string getTop();
    std::string indeck();
    std::string restkitty();
};

#endif

