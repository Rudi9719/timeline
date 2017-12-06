//
//  Player.hpp
//  Timeline
//
//  Created by Gregory Rudolph on 11/29/17.
//  Copyright © 2017 Gregory Rudolph. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Market.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "UIButton.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <iostream>
#include <iterator>
#include <time.h>
#include <algorithm>

class Player {
public:
    
    
    Player(int x, int y, Market* mark);
    
    Market* sharedMarket;
    
    SDL_Rect playerRect;
    UIButton playerButton;
    std::ostringstream filePath;
    SDL_Surface *img;

    int money;
    
    // Player [X, Y]
    int position[2];
    
    SDL_Texture *playerTexture = NULL;
    void movePlayer(int xTransform, int yTransform);
    void setPosition(int x, int y);
    void updateRect();
    void sell(int resource, int count);
    
    int sellAll();
    
private:
    
    int resources[4];
    
 
};


#endif /* Player_hpp */
