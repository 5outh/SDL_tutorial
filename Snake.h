#include "pSnake.h"
#include "pCollectible.h"
#include "Renderer.h"
#include "Timer.h"
#include <vector>
#include "SDL.h"
/* Everything will be laid out on a grid of 20 x 20 squares,
   so all elements will be placed at x and y positions of multiples of 20
   and movement will be done in increments of 20.
*/

enum State {RUNNING, DEAD, STARTSCREEN};

class Snake{
public:
	Snake(); //initialize the game
	pSnake plr; // player
	std::vector<pCollectible> collectibles; //collectibles on screen

	State game_state; //state the game is in
	
	int tick; // time it takes to complete one tick of the game
	int score;
	int w_height; //window height/width (640 x 480)
	int w_width;
	int w_bpp; 
	bool quit; //is the game currently running?

	Timer timer;
	SDL_Event event; // event structure

	SDL_Surface* screen; // main screen to draw to
	SDL_Surface* start_screen;
	SDL_Surface* death_screen;
	SDL_Surface* plr_sprite;
	SDL_Surface* background;

	bool init(); //initialize everything
	void place_collectible(); //add a new collectible

	void setup_game(); // set up the game for playing
	bool is_touching_collectible(); // check if snake is touching a collectible
	bool snake_in_bounds();
	void draw_game(); //draw game based on current state; this is poor design but for such a small project it's fine I think
	void update_game();
	void run_tick();
	void clean_up();
	void main_loop();
};