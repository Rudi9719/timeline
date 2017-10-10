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
    // Generate a deck (stack) and shuffle cards
    Deck(std::vector<Card> cards);
    // Draw the top card from the deck, and remove it
    Card* drawCard();
    
    
private:
    // Vector of unshuffled cards
    std::vector<Card> unshuffled;
    // Vector of shuffled cards in deck
    std::vector<Card> shuffled;
    
};


#endif /* Deck_hpp */
