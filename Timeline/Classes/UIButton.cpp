//
//  UIButton.cpp
//  Timeline
//
//  Created by Rudi on 10/4/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "UIButton.hpp"

UIButton::UIButton() {
    // Uh-oh
}
UIButton::UIButton(SDL_Rect rect) {
    this -> x = rect.x;
    this -> y = rect.y;
    this -> x2 = rect.x + rect.w;
    this -> y2 = rect.y + rect.h;
}

bool UIButton::ownsClick(int x, int y, SDL_Rect rect) {
    if (x > rect.x && x < (rect.x+rect.w)) {

        if (y > rect.y && y < (rect.y+rect.h)) {
            return true;
        }
    }
    return false;
}

void UIButton::moveButton(int xTransform, int yTransform) {
    this -> x += xTransform;
    this -> x2 += xTransform;
    this -> y += yTransform;
    this -> y2 += yTransform;
}
