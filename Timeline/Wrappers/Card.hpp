//
//  Card.hpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
class Card {
public:
    Card();
    void setImage(const char* path);
    void setPosition(int x, int y);
};

#endif /* Card_hpp */
