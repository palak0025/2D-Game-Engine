#include <iostream>
#include "game.h"
#include "logger.h"
#include <glm/glm.hpp>

game::game()
{
    isRunning = false;
    logger::log("Game constructor is called !");
}

game::~game()
{
    logger::log("Game destructor is called !");
}

void game::initialize()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        logger::err("Error initializing SDL !" );
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
        logger::err( "Error creating SDL window !");
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if(!m_renderer)
    {
        logger::err("Error creating SDL renderer !" );
        return;
    }

    //real full screen : actual change video mode to fullscreen
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void game::run()
{
    setup();
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


glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void game::setup()
{
    //TODO : initialize game objects
    //playerPosition.x = 10.0;
    //playerPosition.y = 20.0;
    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(100.0, 0.0);
}

void game::update()
{
    // if we are too fast , waste some time until we reach MILLISECS_PER_FRAME :cap the framerate 
    //while(!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILLISECS_PER_FRAME));
   // int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
   // if(timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
   // {
   //     SDL_Delay(timeToWait); 
   // }

    //difference in ticks since the last frame, converted to seconds
    //NOTE : independent o framerate even if we keep FPS 2 still velocity should be constant of the object
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    
    //store the current frame 
    millisecsPreviousFrame = SDL_GetTicks();
    // update game objects(update frame by frame = velocity)
    playerPosition.x += playerVelocity.x * deltaTime;
    playerPosition.y += playerVelocity.y * deltaTime;
}

void game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_renderer);

    //draw png texture
    SDL_Surface* surface = IMG_Load("../assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    //copy texture to renderer
    SDL_Rect dstRct = {
        static_cast<int>(playerPosition.x), 
        static_cast<int>(playerPosition.y), 
        32, 
        32}; //src rect is NULL as we need full texture(not part of texture) and dstRect in renderer ned to place our texture 
    SDL_RenderCopy(m_renderer, texture, NULL, &dstRct);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(m_renderer); //swap the data from back buffer to front buffer 

}

void game::destroy()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}