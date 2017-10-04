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
    int cardtype;
    int column;
    int paths[4];
    bool comtaken[4];
    int comtype[4];

    
public:
    UIButton cardButton;
    SDL_Rect cardRect;
    Card(SDL_Rect rect);
    int getCardType();
    void setCardType(int);
    int* getPaths();
    int getColumn();
    int* getComType();
    bool* getComTaken();
};
#endif /* Card_hpp */
