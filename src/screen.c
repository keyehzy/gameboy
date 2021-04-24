#include <SDL2/SDL.h>

#include <stdio.h>

SDL_Window *screen = NULL;
SDL_Surface *surface = NULL;

int close_screen()
{
    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_DestroyWindow(screen);
    screen = NULL;

    SDL_Quit();
    return 0;
}

int init_screen()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL failed with %s\n", SDL_GetError());
        exit(1);
    }

    screen =
        SDL_CreateWindow("Stuff", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 160, 144, SDL_WINDOW_SHOWN);

    if (screen == NULL)
    {
        fprintf(stderr, "SDL failed with %s\n", SDL_GetError());
        exit(1);
    }

    surface = SDL_GetWindowSurface(screen);

    return 0;
}

int update_screen()
{
    SDL_Delay(5000);
    close_screen();
    return 0;
}
