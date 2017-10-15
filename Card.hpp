//
//  Card.hpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <vector>
#include "UIButton.hpp"

class Card
{
private:
    int deckPosition;
    int cardtype = 0;
    int column;
    int paths[4];
    bool comtaken[4];
    int comtype[4];
    int r=200,g=200,b=200;

public:
    char* cardName;

    void handleClick(int x, int y);
    UIButton cardButton;
    SDL_Rect cardRect;
    Card(SDL_Rect rect);
    int getCardType();
    void setCardType(int);
    int* getPaths();
    int getColumn();
    void setColumn(int col);
    int* getComType();
    bool* getComTaken();
    void setRGB(int r,int g,int b);
    int getR();
    int getG();
    int getB();
};
#endif /* Card_hpp */
