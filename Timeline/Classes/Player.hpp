//
//  Player.hpp
//  Timeline
//
//  Created by Gregory Rudolph on 11/29/17.
//  Copyright © 2017 Gregory Rudolph. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

class Player {
public:
    Player();
    

    int money;
    // Player [X, Y]
    int position[2];
    void setPosition(int x, int y)
	int getX();
	int getY();
private:

    int resources[4];
    //These are the player positions. You probably already have them but they should be set to the default start card
	//int x = 
	//int y = 
    
 
};


#endif /* Player_hpp */
