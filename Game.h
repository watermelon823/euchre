#ifndef _GAME_H
#define _GAME_H
#include <vector>
#include <string>
#include <memory>
class Deck;
class Player;
class MyDisplay;
class Xwindow;

class Game {
    std::vector<std::unique_ptr<Player>> players;
    std::shared_ptr<Deck> deck;
    std::unique_ptr<MyDisplay> view;
    std::string trumpSuit;
    std::string leadSuit;
    int prevDealerPos;
    int currDealerPos;
    int nextDealerPos;
    bool goAlone;
    std::shared_ptr<Xwindow> xw;
  public:
    Game(Deck* deck, MyDisplay* display, bool debugger,std::shared_ptr<Xwindow> xw0);
    void generate_random_dealer();
    void set_dealer();
    void shuffle_cards(int seed);
    void distribute_cards();
    int get_card(int num, const std::string &ls, const std::string &ts);
    int gameplay(int next_first);
    int call_trump();
    void true_goAlone();
    void end_round(int playerCalled);
    bool end_game();
    void clear_everyone();
    
    ~Game();
};


#endif //EUCHRE_GAME_H

