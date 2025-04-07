#ifndef _SOUNDANDMUSIC__H
#define _SOUNDANDMUSIC__H
extern Mix_Music* music;
extern Mix_Chunk* chunk;
extern Mix_Chunk* win;
extern Mix_Chunk* click;
extern Mix_Chunk* tie;
struct sound {
	void init();
	void createsound();
	void playsound();
	void close();
	void playmusic();
	void playwin();
	void clicksound();
	void tiesound();
	void pausemusic();
};
#endif // !_SOUNDANDMUSIC__H
