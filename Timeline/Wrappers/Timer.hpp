//
//  Timer.hpp
//  Timeline
//
//  Created by Rudi on 9/13/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
    
public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    
    bool is_started();
    bool is_paused();
};
#endif /* Timer_hpp */
