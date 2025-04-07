#include <iostream>
#include <vector>
#include <SDL.h>
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
#undef main

int main() {
    screen Screen;
    Screen.screenwelcome();
    Screen.screenplay2();
    return 0;
}

