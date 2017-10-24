//
//  CardUnitTest.cpp
//  Timeline
//
//  Created by iduR on 6/6/6.
//  Copyright © 2017 iduR-Net. All rights reserved.
//

#include <stdio.h>
#include "Card_hpp"
#include "UIButton.hpp"

SDL_Rect rect;

Card myCard(rect);

//getCardTypeTest
cout << myCard.getCardType() << endl;

//setCardTypeTest
myCard.setCardType(1);
cout << myCard.getCardType() << endl;

//moveCardTest
myCard.moveCard(100,100);

//getPathsTests
int* p;
p = myCard.getPaths();
cout << p << endl;

//handleClickTest
myCard.handleClick(3,4);


//getColumnTest
int col;
col = getColumn();
cout << col << endl;

//getComTypeTest
int* point;
point = getComType();
cout << point << endl;

//getComTakenTest
int* pointer;
pointer = getComTaken();
cout << pointer << endl;





