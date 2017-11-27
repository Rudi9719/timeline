//
//  Deck.hpp
//
//
//  Created by Alexis Walker on 10/20/17.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <random>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <iostream>
#include <iterator>
#include <time.h>
#include <algorithm>

class Deck{
public:
    Deck();
    void printUnshuffled();
    void printShuffled();
    void shuffle();
    void draw();

    std::string getFilePathAtPos(int i);

    int pos;
    char const *drawnCard;

    std::string cardFilePath;
    std::ostringstream tempFilePath;

    SDL_Surface *img = NULL;

    bool end_of_deck = false;

private:
    std::vector<std::string> cardDeck;
    std::vector<std::string> shuffled = std::vector<std::string>(48);
    std::vector<std::string> unshuffled;
};

#endif /* Deck_hpp */
