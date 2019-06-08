#include "Player.h"
using namespace std;

Player::Player(int po, int pa):
score{0},position{po},partner{pa},wonTrick{0},renegeCount{0}, rage_quit{false}, goalone{false} {} 

void Player::setGoAlone() {
    goalone = false;
}

bool Player::getGoAlone() {
    return goalone;
}

void Player::changeDealer() {
    if(isDealer){
        isDealer = false;
    }
    else {
        isDealer = true;
    }
}

int Player::getPos() {
    return position;
}

string Player::getTrump() {
    return trumpSuit;
}

void Player::setTrump(const string &s) {
    trumpSuit = s;
}


int Player::getScore() {
    return score;
}

int Player::getTrick() {
    return wonTrick;
}

int Player::getRenegeCount() {
    return renegeCount;
}

void Player::addScore(int val) {
    score += val;
}

void Player::addWonTrick() {
    wonTrick += 1;
}

void Player::addRenegeCount() {
    renegeCount += 1;
}

void Player::setScore(int val) {
    score = val;
}

void Player::setTrick(int val) {
    wonTrick = val;
}

void Player::setRenegeCount() {
    renegeCount = 0;
}

bool Player::get_rage_quit() {
    return rage_quit;
}

void Player::set_rage_quit() {
    rage_quit = true;
}

Player::~Player(){}

