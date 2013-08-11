#include "SDL.h"
#include "SDL_ttf.h"

class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();
	const char* show_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();


	//The font
	TTF_Font *font;

	//The color of the font
	SDL_Color textColor;
	
	//show the seconds
	SDL_Surface *seconds;

};