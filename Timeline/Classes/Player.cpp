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
    
    this -> playerRect = SDL_Rect();
    this -> playerRect.h = 20;
    this -> playerRect.w = 20;
    this -> playerRect.x = 0;
    this -> playerRect.y = 0;
    this -> playerButton = UIButton(this -> playerRect);
    this -> filePath << "assets/timeline_pawn_small.bmp";
    const char *assetFile = filePath.str().c_str();
    img = SDL_LoadBMP(assetFile);
}

void Player::setPosition(int x, int y) {
    this -> position[0] = x;
    this -> position[1] = y;
    this -> updateRect();
}
void Player::movePlayer(int xTransform, int yTransform) {
    this -> position[0] += xTransform;
    this -> position[1] += yTransform;
    this -> updateRect();
    std::cout << "Player at: (" << position[0] << "," << position[1] << ")" << std::endl;
}
void Player::updateRect() {
    this -> playerRect.x = this -> position[0];
    this -> playerRect.y = this -> position[1];
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
