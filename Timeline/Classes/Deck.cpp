//
//  Deck.cpp
//
//
//  Created by Alexis Walker on 10/20/17.
//

#include "Deck.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <time.h>
#include <string>
#include <algorithm>

Deck::Deck(){
    std::vector<std::string> cardDeck;

    for (pos = 1; pos<shuffled.size(); ++pos){
        tempFilePath << "assets/" << pos << ".bmp";

        cardFilePath = tempFilePath.str();
        cardDeck.push_back(cardFilePath);
        tempFilePath.str("");
    }

   this -> unshuffled = cardDeck;
   this -> shuffled = unshuffled;
    pos = 0;
}

std::string Deck::getFilePathAtPos(int i){
    return shuffled.at(i);
}

void Deck::printUnshuffled(){
    std::copy(unshuffled.begin(), unshuffled.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void Deck::printShuffled(){
    std::copy(shuffled.begin(), shuffled.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

//Shuffle the array
void Deck::shuffle(){
    srand(time(NULL));
    std::random_shuffle(shuffled.begin(), shuffled.end());
}

//Function to draw card
void Deck::draw(){
    if (!end_of_deck){
    //Copies the file path (string) at the indicated position
    cardFilePath = shuffled.at(pos);
    pos++;

    //Needs to be a C char array to be used with SDL
    drawnCard = cardFilePath.c_str();

    img = SDL_LoadBMP(drawnCard);

    std::cout << "\n" << drawnCard << std::endl;

    if (cardFilePath == shuffled.back()) end_of_deck = true;
    }

    if (end_of_deck) std::cout << "\nEnd of deck. No more cards." << std::endl;
}
