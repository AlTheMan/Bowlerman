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

const int WIDTH = 800; 
const int HEIGHT = 450;

PRIVATE void updateMedia(Game newGame);

struct game_type
{
    SDL_Window  *window;
    SDL_Surface *window_surface;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_Texture *player_texture;
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
                                       WIDTH, HEIGHT, 
                                       SDL_WINDOW_SHOWN);
    
    newGame->renderer = SDL_CreateRenderer(newGame->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    newGame->window_surface = SDL_GetWindowSurface(newGame->window);

    newGame->background= loadBackground(newGame, "grass00.bmp");
    //newGame->player_texture = loadBackground(newGame, "pin2.jpg");
    
    Player player1 = initPlayer(500, 500);   //x and y coordinates
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
        /*
        SDL_Surface* surface = IMG_Load("resources/pin.jpg");
        SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);

        SDL_Rect playerRectangle;   //struct to hold the position and size of the sprite
        SDL_QueryTexture(newGame->background, NULL, NULL, &playerRectangle.w, &playerRectangle.h);  //get and scale the dimensions of texture
        playerRectangle.w /=7;                             //scales down width by 7
        playerRectangle.h /=7;                             //scales down height by 7
*/
        updateMedia(newGame);
        SDL_Delay(1000/60); //man behöver ta minus här för att räkna in hur lång tid spelet tar att exekvera
    }
}

// INTE KLAR funktion!
PUBLIC int loadBackground(Game newGame, char fileLocation[])
{
    bool success = true;
    char fileLocationInResources[100]="resources/";
    strcat(fileLocationInResources, fileLocation);
    newGame->window_surface = IMG_Load(fileLocationInResources);
    if(newGame->window_surface == NULL)
    {
        printf("Failed to load surface! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    return SDL_CreateTextureFromSurface(newGame->renderer, newGame->window_surface);;
}

// INTE KLAR funktion!
PUBLIC int loadMedia(Game newGame, char fileLocation[])
{
    bool success = true;
    char fileLocationInResources[100]="resources/";
    strcat(fileLocationInResources, fileLocation);
    newGame->window_surface = IMG_Load(fileLocationInResources);
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