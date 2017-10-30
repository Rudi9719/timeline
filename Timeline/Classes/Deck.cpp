//
//  Deck.cpp
//  Timeline
//
//  Created by Rudi on 10/4/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//


#include "Deck.hpp"
#include <vector>

Deck::Deck(std::vector<Card> cards) {
    this -> unshuffled = cards;
    for(int i = 0; i < 46; i++ ) {
        int random = 0; // fix this
        this -> shuffled.push_back(cards.at(random)); // push back card at random
        // You need to iterate over the unshuffled
        // Look into vector for loop iterator
        // that way you can use erase (iterator)
        cards.erase(<#const_iterator __position#>); // See?
    }
    
}
Card* Deck::drawCard() {
    // Return address of card & remove it
    
    return nullptr; // Haha no.
}
