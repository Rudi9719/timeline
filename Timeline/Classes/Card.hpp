//
//  Card.hpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <vector>
#include "UIButton.hpp"

class Card
{
private:
    
    // position in deck
    int deckPosition;
    // Card type TODO: use enum
    int cardtype = 0;
    // Column card belongs to
    int column;
    // Path array
    int paths[4];
    // Is commodity taken
    bool comtaken[4];
    // Com type
    int comtype[4];
    
    
public:
    // Card name: DEPRECIATED
    char* cardName;
    
    // Move card and underlying UIButton using transforms
    void moveCard(int xTransform, int yTransform);
    
    // Handle click within a card based upon X, Y
    void handleClick(int x, int y);
    
    // The button that determines if a card is clickable
    UIButton cardButton;
    // The card's SDL_rect which is displayed
    SDL_Rect cardRect;
    // Generate a card from SDL Rect
    Card(SDL_Rect rect);
    
    // Get card type: TODO use enum
    int getCardType();
    
    // Set card type: TODO enum
    void setCardType(int);
    
    
    int* getPaths();
    int getColumn();
    int* getComType();
    bool* getComTaken();
};
#endif /* Card_hpp */
