#ifndef GAME_H
#define GAME_H
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS; //each frame 33.3ms  if FPS 30
class game
{
    public:
        game();
        ~game();
        void initialize();
        void run();
        void setup();
        void process_input();
        void update();
        void render();
        void destroy();

        int window_width;
        int window_height;
    
    private:
        bool isRunning;
         int millisecsPreviousFrame = 0;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

};

#endif