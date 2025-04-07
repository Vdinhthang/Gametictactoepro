#include "Globals.h"
#include "soundandmusic.h"
#include <SDL_mixer.h>
#include <iostream>
using namespace std;
Mix_Music* music = NULL;
Mix_Chunk* chunk = NULL;
Mix_Chunk* win = NULL;
Mix_Chunk* click = NULL;
Mix_Chunk* tie = NULL;
void sound::init() {
	if (Mix_Init(0) == -1) {
		cout << "Can't initialize sound" << Mix_GetError() << endl;
	}
}
Mix_Chunk* Loadsound(const char* text) {
	Mix_Chunk* chunk = Mix_LoadWAV(text);
	if (chunk == NULL) {
		cout << "Can't download the " << chunk << endl;
	}
	else {
		return chunk;
	}
}
void sound::createsound() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	music = Mix_LoadMUS("audio/phao.mp3");
	if (music == NULL) {
		cout << "Can't download the music" << endl;
	}
	win = Loadsound("audio/win_sound.wav");
	click = Loadsound("audio/click.wav");
	tie = Loadsound("audio/tie_sound.wav");
}
void sound::playsound() {
	Mix_PlayChannel(-1, chunk, 0);
}
void sound::close() {
	Mix_FreeChunk(chunk);
	Mix_FreeMusic(music);
}
void sound::playmusic() {
	Mix_PlayMusic(music, 0);
}
void sound::playwin() {
	Mix_PlayChannel(-1, win, 0);
}
void sound::clicksound() {
	Mix_PlayChannel(-1, click, 0);
}
void sound::tiesound() {
	Mix_PlayChannel(-1, tie, 0);
}
void sound::pausemusic() {
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}
	else
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
}