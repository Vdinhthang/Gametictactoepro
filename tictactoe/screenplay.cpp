#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include "graphics.h"
#include "clickcontrol.h"
#include "defs.h"
#include "soundandmusic.h"
#include "ttfont.h"
#include "screenplay.h"
using namespace std;

screen Screen;
Graphics graphics;
sound Sound;
Clickcontrol clickcontrol;
font FONT;
void screen::screenwelcome() {
    graphics.init();
    graphics.Loadimage();
    graphics.present();
    Sound.init();
    Sound.createsound();
    FONT.init();
    Sound.playmusic();
    FONT.present();
    graphics.present();
}
void screen::screenplay2() {
    clickcontrol.create();
    clickcontrol.draw();
    int count = 0;
    bool running = true;
    bool aiplay1 = false;
    bool aiplay2 = false;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    Sound.pausemusic();
                }
                if (event.key.keysym.sym == SDLK_1) {
                    clickcontrol.resetClicks(count);
                    aiplay1 = 1;
                }
                if (event.key.keysym.sym == SDLK_2) {
                    clickcontrol.resetClicks(count);
                    aiplay2 = 1;
                }
                if (event.key.keysym.sym == SDLK_3) {
                    clickcontrol.resetClicks(count);
                    aiplay1 = 0;
                    aiplay2 = 0;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (aiplay1 == 1) {
                        if (clickcontrol.handleClick(mouseX, mouseY, count) == 1) {
                            clickcontrol.checkwin(count);
                            clickcontrol.AIClick(count);
                            clickcontrol.draw();
                            clickcontrol.checkwin(count);
                        }
                    }
                    else if (aiplay2 == 1) {
                        if (clickcontrol.handleClick(mouseX, mouseY, count) == 1) {
                            clickcontrol.checkwin(count);
                            clickcontrol.AIClick(count);
                            clickcontrol.draw();
                            clickcontrol.checkwin(count);
                        }
                    }
                    else {
                        clickcontrol.handleClick(mouseX, mouseY, count);
                        clickcontrol.draw();
                        clickcontrol.checkwin(count);
                    }
                }
                graphics.present();
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    clickcontrol.resetClicks(count);
                }
            }
        }
        graphics.present();
    }
    graphics.quit();
}
void screen::screenplaymore() {
    bool running = true;
    SDL_Event event;
    int count = 0;
    clickcontrol.createmore();
    clickcontrol.drawmore();
    Sound.playmusic();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    Sound.pausemusic();
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    clickcontrol.handleClickmore(mouseX, mouseY, count);
                    clickcontrol.checkwinmore(count);
                    clickcontrol.drawmore();
                    clickcontrol.checkwinmore(count);
                    graphics.present();
                }
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    clickcontrol.resetClicksmore(count);
                }
            }
        }
        graphics.present();
        SDL_Delay(160);
    }
    graphics.quit();
}

void screen::screenclosetempt() {
    graphics.quit();
}