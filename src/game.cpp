#include <iostream>
#include "game.h"

game::game()
{
    isRunning = false;
    std::cout<<"constructor is called"<<std::endl;
}

game::~game()
{
    std::cout<<"destructor is called"<<std::endl;
}

void game::initialize()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        std::cerr << "Error initializing SDL" <<std::endl;
        return;
    }
        //fake fullscreen : didn't change video mode to fullscreen
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        window_width = 800;//displayMode.w;
        window_height = 600; //displayMode.h;

        m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS
    );
    if(!m_window)
    {
        std::cerr << "Error creating SDL window" <<std::endl;
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if(!m_renderer)
    {
        std::cerr << "Error creating SDL renderer" <<std::endl;
        return;
    }

    //real full screen : actual change video mode to fullscreen
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void game::run()
{
    while(isRunning)
    {
        process_input();
        update();
        render();
    }
}

void game::process_input()
{
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent))
    {
        switch(sdlEvent.type) 
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
            break;
        }
    }

    
}
void game::update()
{

}
void game::render()
{
    SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);

}
void game::destroy()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}