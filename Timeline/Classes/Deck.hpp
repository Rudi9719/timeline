//
//  Deck.hpp
//  
//
//  Created by Alexis Walker on 10/20/17.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
//#include "../Wrappers/SDL_Wrapper.hpp"
#include <vector>
#include <string>
#include <random>
#include <SDL2_image/SDL_image.h>

class Deck{
public:
    Deck();
    void printUnshuffled();
    void printShuffled();
    void shuffle();
    void draw();
    
    int pos;
    char const *drawnCard;
    
    std::string cardFilePath;
    
    SDL_Surface *img = NULL;
    
    bool end_of_deck = false;
    
private:
    std::vector<std::string> cardDeck;
    std::vector<std::string> shuffled;
    std::vector<std::string> unshuffled;
};

#endif /* Deck_hpp */
