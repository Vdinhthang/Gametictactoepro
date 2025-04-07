#include <iostream>
#include "defs.h"
#include "graphics.h"
#include "Globals.h"
using namespace std;

void Graphics::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init == NULL) {
        cout << "can't initial it";
    }
    else {
        window = SDL_CreateWindow("Winnie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        {
            if (window == NULL) {
                cout << "can't create window" << SDL_GetError() << endl;
            }
            else {
                renderer = SDL_CreateRenderer(window, -1, 0);
                if (renderer == NULL) {
                    cout << "can't create renderer" << SDL_GetError() << endl;
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 238, 238, 238, 238);
                    SDL_RenderClear(renderer);
                }
            }
        }
    }
}
void Graphics::quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void Graphics::present() {
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}
void Graphics::settime() {
    SDL_Delay(3000);
}
SDL_Texture* loadimage(const char* text) {
    SDL_Texture* gtexture = IMG_LoadTexture(renderer, text);
    if (gtexture == NULL) {
        cout << "Can't download image: " << SDL_GetError() << endl;
    }
    else {
        return gtexture;
    }
}
void Graphics::Loadimage() {
    O_CELL = loadimage("D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\cell_o.png");
    X_CELL = loadimage("D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\cell_x.png");
    Empty_CELL = loadimage("D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\cell_empty.png");
    temptimage = X_CELL;
}