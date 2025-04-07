#include "Globals.h"
#include "ttfont.h"
#include <iostream>
using namespace std;
TTF_Font* tictactoe = NULL;
TTF_Font* normalfont = NULL;
TTF_Font* smallfont = NULL;
font gFONT;
void font::init() {
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError;
    }
}
void font::close() {
    TTF_Quit();
    TTF_CloseFont(tictactoe);
}
void font::renderTexture(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}
void font::present() {
    SDL_Color red = { 255,0,0,255 };
    SDL_Color blue = { 0,0,255,255 };
    SDL_Color black = { 0,0,0,0 };
    SDL_Color green = { 0,255,0,255 };
    tictactoe = gFONT.loadFont("freedom.ttf", 90);
    normalfont = gFONT.loadFont("freedom.ttf", 30);
    smallfont = gFONT.loadFont("freedom.ttf", 15);
    title = gFONT.renderText("TICTACTOE", tictactoe, red);
    gFONT.renderTexture(title, 50, 50);
    back = gFONT.renderText("back", normalfont, black);
    gFONT.renderTexture(back, 0, 165);
    replay = gFONT.renderText("(R)replay  (SPACE)pause music", smallfont, green);
    gFONT.renderTexture(replay, 300, 180);
    press = gFONT.renderText("(1)playai1 (2)playai2 (3)playplayer ", smallfont, green);
    gFONT.renderTexture(press, 300, 150);
}
