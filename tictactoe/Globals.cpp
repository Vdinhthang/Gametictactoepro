#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "Globals.h"
using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* O_CELL = NULL;
SDL_Texture* X_CELL = NULL;
SDL_Texture* Empty_CELL = NULL;
SDL_Texture* temptimage = X_CELL;
SDL_Texture* Cells[GRID_SIZE][GRID_SIZE];
SDL_Rect cells[GRID_SIZE][GRID_SIZE];
SDL_Texture* Cellsmore[GRID_SIZEMORE][GRID_SIZEMORE];
SDL_Rect cellsmore[GRID_SIZEMORE][GRID_SIZEMORE];
SDL_Texture* title = NULL;
SDL_Texture* back = NULL;
SDL_Rect backgame; 
SDL_Texture* replay = NULL;
SDL_Texture* press = NULL;