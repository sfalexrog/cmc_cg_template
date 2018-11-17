#include <SDL.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *w = SDL_CreateWindow("CMC Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 800, SDL_WINDOW_OPENGL);

    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}