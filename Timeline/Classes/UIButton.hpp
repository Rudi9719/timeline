//
//  UIButton.hpp
//  Timeline
//
//  Created by Rudi on 10/4/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef UIButton_hpp
#define UIButton_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class UIButton {
public:
    bool ownsClick(int x, int y);
    void moveButton(int xTransform, int yTransform);
    UIButton(SDL_Rect rect);
    UIButton();
    
private:
    int x;
    int y;
    int x2;
    int y2;
    
};


#endif /* UIButton_hpp */
