#include "Game.h"
#include "Windows.h" // debug
#include <stdlib.h> // rand

Game::Game(){
	width = 640;
	height = 480;
	bpp = 32;
	fpsCap = 60;

	if(init() == false){ //sets up screen
		return; //fail!
	}

	Player p;
	player = p;

	spawn_enemies();

	if(load_files() == false){ //load player/background sprite
		return; //FAIL!
	}

	wallBounds.x = width/2;
	wallBounds.y = 25;
	wallBounds.w = 15;
	wallBounds.h = height - 50;


	Renderer r;
	renderer = r;

	Timer t;
	timer = t;
}

void Game::spawn_enemies(){
	Enemy e;
	e.velocity.x = e.speed;
	e.velocity.y = e.speed;
	e.box.x = rand() % (width - e.box.w);  //random number between 0 and window width
	e.box.y = rand() % (height - e.box.h); //random number between 0 and window height

	enemies.push_back(e);
}

bool Game::init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( width, height, bpp, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Avoid the Balls!", NULL );

    //If everything initialized fine
    return true;
}

bool Game::load_files()
{
    //Load the dot image
	player.sprite = renderer.load_image( "square.bmp" );
	for(int i = 0; i < enemies.size(); i++){
		enemies[i].sprite = renderer.load_image( "dot.bmp" );
	}

    //If there was a problem in loading the dot
    if( player.sprite == NULL )
    {
        return false;
    }

	background = renderer.load_image("background.bmp");

	if(background == NULL){
		return false;
	}

	timer.start();

    //If everything loaded fine
    return true;
}

void Game::clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( player.sprite );

	for(int i=0; i<enemies.size(); i++){
		SDL_FreeSurface( enemies[i].sprite );
	}

    //Quit SDL
    SDL_Quit();
}

void Game::render_game(){

    //show background
	//renderer.apply_surface(0,0,background,screen);

	//fill screen white
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

	//Show the wall
	renderer.render_rectangle(screen, &wallBounds);

	//show player and enemies on screen
	renderer.apply_surface(player.box.x, player.box.y, player.sprite, screen);
	for(int i = 0; i < enemies.size(); i++){
		renderer.apply_surface(enemies[i].box.x, enemies[i].box.y, enemies[i].sprite, screen);
	}
}

void Game::move_player(){ 
    //Move the square left or right
    player.box.x += player.velocity.x;
       
    //If the square went too far to the left or right or has collided with the wall
    if( ( player.box.x < 0 ) || ( player.box.x + player.box.w > width ) || ( c_test.check_collision(&(player.box), &wallBounds ) ) )
    {
        //Move back
        player.box.x -= player.velocity.x;
    }
    
    //Move the square up or down
    player.box.y += player.velocity.y;
    
    //If the square went too far up or down or has collided with the wall
    if( ( player.box.y < 0 ) || ( player.box.y + player.box.h > height ) || ( c_test.check_collision(&(player.box), &wallBounds ) ) )
    {
        //Move back
        player.box.y -= player.velocity.y;
    }
	
}

bool Game::move_enemy(Enemy* e){
	
    //Move the square left or right
    (*e).box.x += (*e).velocity.x;
       
    //If the enemy went too far to the left or right
    if( ( (*e).box.x < 0 ) || ( (*e).box.x + (*e).box.w > width ) )
    {
        //Reverse direction
        (*e).velocity.x = -(*e).velocity.x;
    }
    
    //Move the square up or down
    (*e).box.y += (*e).velocity.y;
    
    //If the enemy went too far up or down
    if( ( (*e).box.y < 0 ) || ( (*e).box.y + (*e).box.h > height ))
    {
        //Reverse direction
        (*e).velocity.y = -(*e).velocity.y;
    }

	for(int i = 0; i < enemies.size(); i++){
			if(c_test.check_collision(&(player.box), &(enemies[i].box))){ //if an enemy hits the player
				player.box.x = 0; //reset player position
				player.box.y = 0;

				//reset enemies
				reset_enemies();
				return false; //player collided with enemy, end the game
			}
	}
	return true; //player didn't collide with enemy, continue on...
}

void Game::setup_enemy(){
	Enemy e;
	e.box.x = rand() % (width - e.box.w);  //random number between 0 and window width
	e.box.y = rand() % (height - e.box.h); //random number between 0 and window height
	e.setSpeed(enemies.begin()->speed); //set speed to existing enemy speed
	e.sprite = renderer.load_image( "dot.bmp" ); //set sprite
	enemies.push_back(e); //add enemy
}

//convenience function to move all enemies at once
bool Game::move_enemies(){
	for(int i = 0; i < enemies.size(); i++){
		if(!move_enemy(&(enemies[i]))){
			return false;
		};
	}
	return true;
}

//for debug purposes
std::string Game::toString(){
	std::stringstream ss;
	
	ss << "Player Position: (" 
	   << player.box.x << "," << player.box.y << 
	   ")\n";

	ss << "Player Velocity: (" 
	   << player.velocity.x << "," << player.velocity.y 
	   << ")\n";

	ss << "Timer ticks: "
	   << timer.get_ticks()
	   << "\n";

	for(int i = 0; i < enemies.size(); i++){

		ss << "Enemy Velocity: (" 
		   << enemies[i].velocity.x << "," << enemies[i].velocity.y
	       << ")\n";
	}

	return ss.str();
}

void Game::reset_enemies(){
	/*for(int i = 0; i < enemies.size(); i++){
		SDL_FreeSurface(enemies[i].sprite);
	}
	enemies.clear();*/

	enemies.clear();
	setup_enemy();
	setup_enemy();

}

void Game::main_loop(){
    //Quit flag
    bool quit = false;

	Timer fps;

	timer.start();

	int ticks = timer.get_ticks();
	int last_ticks = 0;

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the player
            player.handle_input(event);
			OutputDebugString(toString().c_str());

            //If the user has clicked X
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

		if(ticks - last_ticks > 10000){ // if it has been ten seconds since the last enemy spawned
			last_ticks = ticks;
			//step up speed for existing enemies
			for(int i = 0; i < enemies.size(); i++){
				enemies[i].setSpeed(enemies[i].speed + 0.5f);
			}
			//add an enemy
			setup_enemy();
		}

		//Move enemies and player
		if(!move_enemies()){ //if there was a collision between enemies and player
			quit = true;     //quit the game altogether
		}
		move_player();
		
        //Render background
        //Show the dot on the screen
        render_game();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return; //FAIL!
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / fpsCap )
        {
            SDL_Delay( ( 1000 / fpsCap ) - fps.get_ticks() );
        }
		ticks = timer.get_ticks();
    }
	//stop timer
	timer.stop();

    //Clean up
    clean_up();
}