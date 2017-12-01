//
//  Player.cpp
//  Timeline
//
//  Created by Gregory Rudolph on 11/29/17.
//  Copyright © 2017 Gregory Rudolph. All rights reserved.
//

#include "Player.hpp"

Player::Player(int x, int y) {
    this -> position[0] = x;
    this -> position[1] = y;
    
    this -> money = 0;
}

void Player::setPosition(int x, int y) {
    this -> position[0] = x;
    this -> position[1] = y;
    
}
