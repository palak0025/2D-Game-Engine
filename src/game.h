#ifndef GAME_H
#define GAME_H
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>

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
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

};

#endif