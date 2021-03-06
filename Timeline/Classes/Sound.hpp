//
//  Sound.hpp
//  Timeline
//
//  Created by Taylor Hines on 11/13/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Sound_hpp
#define Sound_hpp

#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Sound {
public:
    Sound();
    void closeSound();
    bool loadSound();
    void playAll();
    void playShuffle();
    void playPlacement();

private :
Mix_Chunk *CardShuffle = NULL;

Mix_Chunk *CardPlacement = NULL;


};


#endif /* Sound_hpp */
