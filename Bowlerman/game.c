#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"

#define PUBLIC /* empty */
#define PRIVATE static
#define LENGTH 100

const int HEIGHT = 1280;
const int WIDTH = 720;

PRIVATE void updateMedia(Game newGame);

struct game_type
{
    SDL_Window  *window;
    SDL_Surface *window_surface;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_Event    window_event;
};

PUBLIC Game createGame()
{
    Game newGame = malloc(sizeof(struct game_type));
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Failed to initialize SDL2: %s\n", SDL_GetError());
    }
    newGame->window= SDL_CreateWindow("Bowlerman 0.1", 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       HEIGHT, WIDTH, 
                                       SDL_WINDOW_SHOWN);
    
    newGame->renderer = SDL_CreateRenderer(newGame->window, -1, 0);
    newGame->window_surface = SDL_GetWindowSurface(newGame->window);

    loadBackground(newGame, "grass00.bmp");
    
    Player player1 = initPlayer();

    return newGame;
}

PUBLIC void gameUpdate(Game newGame)
{
    bool keep_window_open = true;
    while(keep_window_open)
    {
        while(SDL_PollEvent(&newGame->window_event) > 0)
        {
            SDL_Event test = newGame->window_event;
            
            switch(newGame->window_event.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }
        }
        updateMedia(newGame);
        SDL_Delay(1000/60);
    }
}

// INTE KLAR funktion!
PUBLIC int loadBackground(Game newGame, char fileLocation[])
{
    bool success = true;

    newGame->window_surface = IMG_Load("resources/grass00.bmp");
    if(newGame->window_surface == NULL)
    {
        printf("Failed to load surface! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    newGame->background = SDL_CreateTextureFromSurface(newGame->renderer, newGame->window_surface);

    return success;
}

// INTE KLAR funktion!
PUBLIC int loadMedia(Game newGame, char fileLocation[])
{
    bool success = true;

    newGame->window_surface = IMG_Load("resources/grass00.bmp");
    if(newGame->window_surface == NULL)
    {
        printf("Failed to load surface! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    newGame->background = SDL_CreateTextureFromSurface(newGame->renderer, newGame->window_surface);

    return success;
}

PRIVATE void updateMedia(Game newGame)
{
    SDL_RenderClear(newGame->renderer);
    SDL_RenderCopy(newGame->renderer, newGame->background, NULL, NULL);
    //SDL_RenderCopy(newGame->renderer, newGame->player, destination, NULL);
    SDL_RenderPresent(newGame->renderer);
}

PUBLIC void destroyGame(Game theGame)
{
    SDL_DestroyTexture(theGame->background);
    SDL_DestroyRenderer(theGame->renderer);
    SDL_FreeSurface(theGame->window_surface);
    SDL_DestroyWindow(theGame->window);
    SDL_Quit();
}