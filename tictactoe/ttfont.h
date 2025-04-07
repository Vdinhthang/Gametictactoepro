#ifndef _TTFONT__H
#define _TTFONT__H
#include <string>
#include "Globals.h"
extern TTF_Font* tictactoe;
extern TTF_Font* normalfont;
extern TTF_Font* smallfont;
struct font {
    void init();
    void close();
    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont(path, size);
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
        return gFont;
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
        if (textSurface == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface(textSurface);
        return texture;
    }
    void renderTexture(SDL_Texture* texture, int x, int y);
    void present();
};
#endif // !_TTFONT__H

