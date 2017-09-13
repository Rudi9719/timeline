#include <SDL.h>
#include <stdbool.h>
#include <string>
#include <iostream>

using namespace std;

const int width = 1000;
const int height = 800;
 const int frame_rate = 30; // Desired FPS
const int card_height = 100;
const int card_width = 80;

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

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    started = false;
    paused = false;
}

void Timer::pause()
{
    if((started==true)&&(paused==false))
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if(paused==true)
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    if(started==true)
    {
        if(paused==true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main (int argc, char** argv)
{
int frame = 0;
Timer fps;
bool cap = true;
bool quit = false;
bool r2_red = false;
SDL_Window* window = NULL;
window = SDL_CreateWindow("Card Test", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);

SDL_Event e;
// Setup renderer
SDL_Renderer* renderer = NULL;
renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

// Clear window
SDL_RenderClear(renderer);

// Create a rect
SDL_Rect r1;
r1.x = (width/2)-(90*1.5);
r1.y = 348;
r1.w = card_width;
r1.h = card_height;
SDL_Rect r2;
r2.x = (width/2)-(90*.5);
r2.y = 348;
r2.w = card_width;
r2.h = card_height;
SDL_Rect r3;
r3.x = (width/2)+(90*.5);
r3.y = 348;
r3.w = card_width;
r3.h = card_height;

while (!quit) {
    fps.start();
    while (SDL_PollEvent(&e)!=0) {
        if (e.type==SDL_QUIT)
            quit=true;
        if (e.type==SDL_KEYDOWN){
            if (e.key.keysym.sym==SDLK_RETURN){
                r2_red=(!r2_red);
                cap=(!cap);
            }
            if ((e.key.keysym.sym==SDLK_w)&&(r2.y>0)){
                r2.y = r2.y-(card_height/4);
            }
            if ((e.key.keysym.sym==SDLK_s)&&(r2.y<=height-card_height-25)){
                r2.y = r2.y+(card_height/4);
            }
        }
    }
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear(renderer);
    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 200, 200, 200,255);

    // Render rect
    SDL_RenderFillRect( renderer, &r1);
    if(r2_red == true) {
        SDL_SetRenderDrawColor( renderer, 200, 0, 0,255);
        SDL_RenderFillRect( renderer, &r2);
        SDL_SetRenderDrawColor( renderer, 200, 200, 200,255);
    }
    else {
        SDL_RenderFillRect( renderer, &r2);
    }
    SDL_RenderFillRect( renderer, &r3);

    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    // Wait for 5 sec
    //SDL_Delay( 5000 );
    frame++;
    if((cap==true)&&(fps.get_ticks() < 1000/frame_rate))
    {
        SDL_Delay((1000/frame_rate)-fps.get_ticks());
        cout << "delaying for " << (1000/frame_rate)-fps.get_ticks() << " ms" << endl;
    }
}
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
