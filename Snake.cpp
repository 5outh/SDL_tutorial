#include "Snake.h"
#include "Windows.h"
#include <sstream>

Snake::Snake(){
 	w_height = 480; //window height/width (640 x 480)
	w_width = 640;
	w_bpp = 32; 

	if(!init()){
		return; //fail!
	}

	tick = 80; // in ms
	
	setup_game();

	death_screen = Renderer::load_image("dead_screen.bmp");
	if(death_screen == NULL){
		OutputDebugString("Death Screen Null");
	}
	start_screen = Renderer::load_image("start_screen.bmp");
	background = Renderer::load_image("background.bmp");
	
	std::vector<pCollectible> collectibles; //collectibles on screen

	game_state = STARTSCREEN;

	Timer t;
	timer = t;
};

void Snake::setup_game(){
	pSnake p; // make a new player	
	plr = p;

	plr_sprite = Renderer::load_image("player_sprite.bmp");
	plr.segment_sprite = Renderer::load_image("player_sprite.bmp");

	collectibles.clear();
	place_collectible();
	quit = false;
	score = 0;
}

bool Snake::init(){ //initialize everything
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( w_width, w_height, w_bpp, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Snake", NULL );

    //If everything initialized fine
    return true;
};

void Snake::place_collectible(){ //add a new collectible
	pCollectible coll(Renderer::load_image("collectible_sprite.bmp"));
	collectibles.push_back(coll);
}; 

bool Snake::is_touching_collectible(){ // check if snake is touching a collectible
	for(int i=0; i< collectibles.size(); i++){
		if(plr.segments.front().box->x == collectibles[i].box->x &&
		   plr.segments.front().box->y == collectibles[i].box->y){
			return true;
		}
	}
	return false;
}; 

bool Snake::snake_in_bounds(){
	SDL_Rect* seg = plr.segments.front().box;
	return seg->x > - (plr.segments.front().box->w)
		&& seg->x < w_width
		&& seg->y > - (plr.segments.front().box->h)
		&& seg->y < w_height;
};

void Snake::draw_game(){ 
	if(game_state == RUNNING){
		Renderer::apply_surface(0,0,background,screen); //draw background
		for(int i=0; i< collectibles.size(); i++){
			collectibles[i].draw(screen);
		}

		plr.draw(screen);
	}else if(game_state == DEAD){
		Renderer::apply_surface(0,0,death_screen,screen); //show death screen
	}else if(game_state == STARTSCREEN){
		Renderer::apply_surface(0,0,start_screen,screen); //show start screen
	}
}; 

void Snake::update_game(){
	bool event_handled = false;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			quit = true;
			return; //no need to do anything else
		}else{
			if(game_state == RUNNING){
				if(plr.handle_input(&event)){
					event_handled = true;
				}
			}if(game_state == DEAD){
				if(event.type == SDL_KEYDOWN){
					if(event.key.keysym.sym == SDLK_r){
						game_state = RUNNING;
						setup_game();
					}
				}
			}if(game_state == STARTSCREEN){
				if(event.type == SDL_KEYDOWN){
					if(event.key.keysym.sym == SDLK_RETURN){
						game_state = RUNNING;
					}
				}
			}
		}
	}

};

void Snake::run_tick(){
	if(game_state == RUNNING){
		if(game_state == RUNNING){
			if(is_touching_collectible()){
				plr.add_segment(); //add segment and move player
				collectibles.pop_back(); //get rid of current collectible
				place_collectible(); //place a new collectible on screen
			}else{
				plr.move(); //move player
			}
		}
		plr.update(); // update player
		draw_game(); //draw game
		if(plr.is_colliding() || !snake_in_bounds()){
			game_state = DEAD; //if snake got dead, set state to dead
		}
	}
};


void Snake::clean_up(){
	SDL_FreeSurface(death_screen);
	SDL_FreeSurface(start_screen);
	SDL_FreeSurface(plr.segment_sprite);
	SDL_FreeSurface(background);
	SDL_FreeSurface(collectibles.front().sprite);
	SDL_Quit();
}

void Snake::main_loop(){
	timer.start();
	int last_ticks = 0;
	while(!quit){
		update_game();
		if(game_state == RUNNING){
			if(last_ticks < tick){
				OutputDebugString("Run Tick now:\n");
				run_tick();
				SDL_Delay(tick - last_ticks);
				last_ticks = 0;
			}
		}else{
			update_game();
			draw_game();
		}
		if(SDL_Flip(screen) == -1){
			OutputDebugString("Error flipping screen!!");
			//FAIL SOUP!
		}
	}
	timer.stop();
	clean_up();
};