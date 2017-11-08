//
//  Card.cpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "Card.hpp"
#include <iostream>


Card::Card(SDL_Rect rect)
{

    this -> cardButton = UIButton(rect);
    this -> cardtype = -1;
    column = -1;
    for (int i = 0; i > 4; i++) {
       this -> paths[i] = -1; // give paths placer values
    }
    for (int i = 0; i > 4;i++) {
        this -> comtaken[i] = false; // gives commodity bools placer values
    }
    for (int i = 0; i > 4;i++) {
        this -> comtype[i] = -1; // gives comtypes placer values
    }
    this -> cardRect = rect;
}
SDL_Surface* Card::getCardSurface()
{
    return cardSurfaceImg;
}
SDL_Texture* Card::getCardTexture()
{
    return cardTextureImg;
}
int Card::getCardType()
{
    return cardtype;
}
void Card::setCardType(int _cardtype)
{
    this -> cardtype = _cardtype;
}

int* Card::getPaths() {
    return this -> paths;
}
void Card::handleClick(int x, int y) {
    switch (this -> getCardType()) {
        case 9:
            printf("Help card clicked.\n");
            std::cout << "Help card clicked." << std::endl;
            system("open http://cheapass.com//wp-content/uploads/2016/07/TIMELINE-RULES.pdf");
            break;
        default:
            printf("Undefined card type, %d clicked.\n", this -> getCardType());
            break;

    }
}

int Card::getColumn() {
    return this -> column;
}
void Card::setColumn(int col) {
    this -> column = col;
}
int* Card::getComType() {
    return this -> comtype;
}
bool* Card::getComTaken() {
    return this -> comtaken;
}

void Card::setRGB(int r_new,int g_new,int b_new) {
    this -> r = r_new;
    this -> g = g_new;
    this -> b = b_new;
}
int Card::getR() {
    return this -> r;
}
int Card::getG() {
    return this -> g;
}
int Card::getB() {
    return this -> b;
}

int Card::getY() {
    return this->cardRect.y;
}
void Card::setY(int y_new) {
    this->cardRect.y = y_new;
}
int Card::getX() {
    return this->cardRect.x;
}
void Card::setX(int x_new) {
    this->cardRect.x = x_new;
}
