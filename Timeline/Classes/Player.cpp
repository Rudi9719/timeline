//
//  Player.cpp
//  Timeline
//
//  Created by Gregory Rudolph on 11/29/17.
//  Copyright © 2017 Gregory Rudolph. All rights reserved.
//

#include "Player.hpp"



Player::Player(int x, int y, Market* mark) {
    this -> position[0] = x;
    this -> position[1] = y;
    this -> sharedMarket = mark;
    this -> money = 0;
}

void Player::setPosition(int x, int y) {
    this -> position[0] = x;
    this -> position[1] = y;
    
}

void Player::sell(int resource, int count) {
    this -> money += (sharedMarket->valueOf[resource] * count);
}

int Player::sellAll() {
    for (int i = 0; i < 4; i++) {
        this -> sell(i, this -> resources[i]);
    }
    return this -> money;
}
