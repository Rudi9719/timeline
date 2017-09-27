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


class Card
{
private:
    int cardtype;
    int column;
    int y;
    int paths[4];
    bool comtaken[4];
    int comtype[4];
    
public:
    Card();
    int getCardType();
    void setCardType(int);
    int getY();
    void setY(int);
    int* getPaths();
    int getColumn();
    int* getComType();
    bool* getComTaken();
};
#endif /* Card_hpp */
