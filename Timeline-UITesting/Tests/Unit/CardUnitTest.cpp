//
//  CardUnitTest.cpp
//  Timeline
//
//  Created by iduR on 6/6/6.
//  Copyright © 2017 iduR-Net. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include "../../Classes/Card.hpp"
#include "UIButton.hpp"


using namespace std;


int main() {
    SDL_Rect rect;
    
    Card myCard(rect);
    
    cout << "getCardTypeTest" << endl;
    cout << myCard.getCardType() << endl;
    
    cout << "setCardTypeTest" << endl;
    myCard.setCardType(1);
    cout << myCard.getCardType() << endl;
    
    cout << "moveCardTest" << endl;
    cout << "Old (x, y) : (" << myCard.cardRect.x;
    cout << " , " << myCard.cardRect.y << ")" << endl;
    myCard.moveCard(4,4);
    cout << "New (x, y) : (" << myCard.cardRect.x;
    cout << " , " << myCard.cardRect.y << ")" << endl;
    
    cout << "getPathsTests" << endl;
    cout << *myCard.getPaths() << endl;
    
    cout << "handleClickTest" << endl;
    myCard.handleClick(3,4);
    
    
    cout << "getColumnTest" << endl;
    int col;
    col = myCard.getColumn();
    cout << col << endl;
    
    cout << "getComTypeTest" << endl;
    cout << *myCard.getComType() << endl;
    
    cout << "getComTakenTest" << endl;
    cout << *myCard.getComTaken()  << endl;
    
}



