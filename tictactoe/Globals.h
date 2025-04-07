#ifndef _GLOBALS__H
#define _GLOBALS__H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "defs.h"
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* O_CELL;
extern SDL_Texture* X_CELL;
extern SDL_Texture* Empty_CELL;
extern SDL_Texture* temptimage;
extern SDL_Texture* Cells[GRID_SIZE][GRID_SIZE];
extern SDL_Rect cells[GRID_SIZE][GRID_SIZE];
extern SDL_Texture* Cellsmore[GRID_SIZEMORE][GRID_SIZEMORE];
extern SDL_Rect cellsmore[GRID_SIZEMORE][GRID_SIZEMORE];
extern SDL_Rect backgame;
extern SDL_Texture* title;
extern SDL_Texture* back;
extern SDL_Texture* replay;
extern SDL_Texture* press;

#endif // !_GLOBALS__H

