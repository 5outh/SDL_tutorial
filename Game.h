#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"
#include "CollisionTester.h"
#include <string>
#include <sstream>
#include <vector>
#include "SDL_ttf.h"

class Game{
public:
	Game();
	Game(int, int, int); //width, height, bpp
	
	SDL_Surface* screen; //main screen
	SDL_Surface* background; //background sprite
	SDL_Rect wallBounds;
	SDL_Event event;

	Player player; //main player
	std::vector<Enemy> enemies;
	Renderer renderer; //renderer for surfaces
	CollisionTester c_test; //collision tester
	Timer timer;
	
	int width;
	int height;
	int bpp;
	int fpsCap;
	std::stringstream time;

	bool init();
	bool load_files();
	void clean_up();
	void render_game();

	void main_loop();

	void move_player();
	bool move_enemies();
	bool move_enemy(Enemy* e);

	void spawn_enemies();
	void setup_enemy();
	void reset_enemies();

	std::string toString();
};