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

class Player {
public:
    
    
    Player(int x, int y, Market* mark);
    
    Market* sharedMarket;
    

    int money;
    
    // Player [X, Y]
    int position[2];
    
    void movePlayer(int xTransform, int yTransform);
    void setPosition(int x, int y);
    
    void sell(int resource, int count);
    
    int sellAll();
    
private:
    
    int resources[4];
    
 
};


#endif /* Player_hpp */
