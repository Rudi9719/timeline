//
//  Deck.hpp
//  Timeline
//
//  Created by Rudi on 10/4/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include <vector>
#include "SDL_Wrapper.hpp"

class Deck {
public:
    Deck(std::vector<Card> cards);
    std::vector<Card>* deck;
    
private:
    std::vector<Card> unshuffled;
    std::vector<Card> shuffled;
    
};


#endif /* Deck_hpp */
