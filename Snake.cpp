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

	tick = 50; // in ms
	pSnake plr; // player	
	plr_sprite = Renderer::load_image("player_sprite.bmp");
	plr.segment_sprite = Renderer::load_image("player_sprite.bmp");
	
	std::vector<pCollectible> collectibles; //collectibles on screen

	game_state = RUNNING;

	score = 0;

	quit = false;

	Timer t;
	timer = t;
	
	place_collectible();
};

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
	return seg->x > 0
		&& seg->x < w_width
		&& seg->y > 0
		&& seg->y < w_height;
};

void Snake::draw_game(){ 
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	if(game_state == RUNNING){
		for(int i=0; i< collectibles.size(); i++){
			collectibles[i].draw(screen);
		}
	}

	if(plr.segment_sprite == NULL){
		plr.segment_sprite = Renderer::load_image("player_sprite.bmp"); //really weird, this always fires.
	}

	plr.draw(screen);
}; 

void Snake::update_game(){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			quit = true;
			return; //no need to do anything else
		}else{
			if(game_state == RUNNING){
				plr.handle_input(&event);
			}
		}
	}
	if(game_state == RUNNING){
		if(is_touching_collectible()){
			plr.add_segment(); //add segment and move player
			collectibles.pop_back(); //change collectible location
			place_collectible();
		}else{
			plr.move(); //move player
		}
	}

};

void Snake::run_tick(){
	if(game_state == RUNNING){
		plr.update(plr.segments.front().direction);
		draw_game();
		if(plr.is_colliding() || !snake_in_bounds()){
			game_state = DEAD; //if snake got dead, set state to dead
		}
	}
	update_game();
};

void Snake::main_loop(){
	timer.start();
	int last_ticks = 0;
	while(!quit){
		if(game_state == RUNNING){
			if(last_ticks < tick){
				run_tick();
				SDL_Delay(tick - last_ticks);
				last_ticks = 0;
			}

			if(SDL_Flip(screen) == -1){
				OutputDebugString("Error flipping screen!!");
				//FAIL SOUP!
			}
		}else{
			run_tick();
		}
	}
	timer.stop();
};