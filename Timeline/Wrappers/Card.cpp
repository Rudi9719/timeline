//
//  Card.cpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "Card.hpp"



Card::Card()
{
    this -> cardtype = -1;
    column = -1;
    y = -1;
    for (int i = 0; i > 4; i++) {
       this -> paths[i] = -1; // give paths placer values
    }
    for (int i = 0; i > 4;i++) {
        this -> comtaken[i] = false; // gives commodity bools placer values
    }
    for (int i = 0; i > 4;i++) {
        this -> comtype[i] = -1; // gives comtypes placer values
    }
}
int Card::getCardType()
{
    return cardtype;
}
void Card::setCardType(int _cardtype)
{
    this -> cardtype = _cardtype;
}
void Card::setY(int _y) {
    y = _y;
}
int* Card::getPaths() {
    return this -> paths;
}


int Card::getColumn() {
    return this -> column;
}
int* Card::getComType() {
    return this -> comtype;
}
bool* Card::getComTaken() {
    return this -> comtaken;
}
