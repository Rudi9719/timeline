//
//  main.cpp
//  Timeline
//
//  Created by Gregory Rudolph-Alverson on 9/11/17.
//  Copyright © 2017 CS350. All rights reserved.
//

#include <iostream>
#include "Wrappers/SDL_Wrapper.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    SDL_Wrapper wrapper = SDL_Wrapper(1000, 1000);
    SDL_Delay(5000); // Replace this with main event loop
    
    std::cout << "Hello, World!\n";
    return 0;
}
