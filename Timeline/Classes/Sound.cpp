//
//  Sound.cpp
//  Timeline
//
//  Created by Taylor Hines on 11/13/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "Sound.hpp"


Sound::Sound(){}

bool Sound::loadSound(){
//Loading success flag
bool success = true;

//Load sound effects
CardShuffle = Mix_LoadWAV( "../assets/Card_Shuffle.wav" );
if( CardShuffle == NULL )
{
    printf( "Failed to load shuffle sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
}

CardPlacement = Mix_LoadWAV( "../assets/Card_Placement.wav" );
if( CardPlacement == NULL )
{
    printf( "Failed to load Placement sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
}

return success;

}
void Sound::closeSound()
{
    Mix_FreeChunk(CardShuffle);
    Mix_FreeChunk(CardPlacement);
    CardShuffle = NULL;
    CardPlacement = NULL;

}




