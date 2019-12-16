#include "MyGame.h"

namespace GMUCS425
{
	//game singleton
	MyGame * gGame=NULL;
	MyGame * getMyGame(){ return gGame; }
	void setMyGame(MyGame * game){ gGame=game; }
	//define the game prototype

	//music track
	Mix_Music *gMusic = NULL;

	bool MyGame::init(const std::string name)
	{
		using namespace std;

		//Initialization flag
		bool success = true;

		//Initialize SDL
		if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		{
			cerr<<"ERROR: SDL could not initialize! SDL Error: "<<SDL_GetError()<<endl;
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			{
				cerr<<"WARNING: Linear texture filtering not enabled!" <<endl;
			}

			//Create window
			gWindow = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if( gWindow == NULL )
			{
				cerr<<"ERROR: Window could not be created! SDL Error: "<<SDL_GetError()<<endl;
				success = false;
			}
			else
			{
				//Create vsynced renderer for window
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
				if( gRenderer == NULL )
				{
					cerr<<"ERROR: Renderer could not be created! SDL Error: "<< SDL_GetError() <<endl;
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) )
					{
						cerr<<"ERROR: SDL_image could not initialize! SDL_image Error: "<<IMG_GetError()<<endl;
						success = false;
					}

					//initialize font
					if( TTF_Init() == -1 )
					{
						cerr<<"ERROR: SDL_ttf could not initialize! SDL_ttf Error:  "<<TTF_GetError()<<endl;
						success = false;
					}

					//Initialize SDL_mixer
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
						success = false;
					}
				}
			}
		}

		return success;
	}

	bool MyGame::loadMedia(const std::string & config)
	{
		//create only one level, in the future, we will use config file
		//to create multiple levels
		gMusic = Mix_LoadMUS("sound\\background.wav");
		stun = Mix_LoadWAV("sound\\magnemite.wav");
		level_up = Mix_LoadWAV("sound\\level_up.wav");
		lose = Mix_LoadWAV("sound\\gastly.wav");
		item = Mix_LoadWAV("sound\\porygon.wav");
		if (gMusic == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}
	  if( !this->m_SceneManager.create("level01", config, true) ) return false;
	  if (!this->m_SceneManager.create("level02", "levels\\level002.txt", false)) return false;
	  if (!this->m_SceneManager.create("level03", "levels\\level003.txt", false)) return false;
	  if (!this->m_SceneManager.create("level04", "levels\\level004.txt", false)) return false;
	  if (!this->m_SceneManager.create("level05", "levels\\level005.txt", false)) return false;
	  if (!this->m_SceneManager.create("gameOver", "levels\\GameOver.txt", false)) return false;
	  if (!this->m_SceneManager.create("win", "levels\\win.txt", false)) return false;
		return true;
	}

	void MyGame::resizeWidow(int w, int h)
	{
		if(w>h)
	    SCREEN_HEIGHT=(int)(SCREEN_WIDTH*h*1.0f/w);
	  else
	    SCREEN_WIDTH=(int)(SCREEN_HEIGHT*w*1.0f/h);
	  SDL_SetWindowSize(getMyGame()->getWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	void MyGame::incrementLevel() {
		this->lvl++;
		printf("Current Level: %d", this->lvl);
	}

	void MyGame::incrementScore(int amount) {
		this->score += amount;
	}
	void MyGame::decrementLives() {
		this->lives-= 0.5;
	}

	void MyGame::run()
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Current animation frame
		unsigned int frame = 0;

		std::list<MyScene *> allScenes;
		m_SceneManager.getAll(allScenes);

		//While application is running
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		while( !quit )
		{
			if (lives <= 0) {
				this->setLevel();
			}
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT || keys[SDL_SCANCODE_ESCAPE])
				{
					quit = true;
				}
				else
				{
					int i;
					int k;
					switch (this->lvl)
					{
						//special case: game over level
						case 0:
							i = 6;
							k = 0;
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
						case 1:
							i = 0;
							k = 0;
							//if music not playing, play music.
							if (Mix_PlayingMusic() == 0)
							{
								Mix_PlayMusic(gMusic, -1);
							}
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
						case 2:
							i = 1;
							k = 0;
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
						case 3:
							i = 2;
							k = 0;
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
						case 4:
							i = 4;
							k = 0;
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
						case 5:
							i = 5;
							k = 0;
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
						case 6:
							i = 3;
							k = 0;
							Mix_HaltMusic();
							Mix_FreeMusic(gMusic);
							gMusic = Mix_LoadMUS("sounds/victory.mp3");
							//if music not playing, play music.
							if (Mix_PlayingMusic() == 0)
							{
								Mix_PlayMusic(gMusic, -1);
							}
							for (MyScene * s : allScenes)
							{
								if (k == i)
								{
									s->activate();
								}
								else
								{
									s->deactive();
								}
								k++;
							}
							break;
					}
					
					for(MyScene * scene : allScenes)
						if(scene->is_active()) scene->handle_event(e);
				}
			}

			//std::cout<<"---------- UPDATE ---------- "<<std::endl;

			for(MyScene * scene : allScenes) if(scene->is_active()) scene->update();

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			//Render current frame
			for(MyScene * scene : allScenes) if(scene->is_active()) scene->display();
			for(MyScene * scene : allScenes) if(scene->is_active()) scene->draw_HUD();

			//Update screen
			SDL_RenderPresent( gRenderer );

			//sleep for a short amount of time
			SDL_Delay(30);

			//Go to next frame
			++frame;
		}
	}


	void MyGame::close()
	{
		//Destroy window
		SDL_DestroyRenderer( gRenderer );
		SDL_DestroyWindow( gWindow );
		gWindow = NULL;
		gRenderer = NULL;

		//frees the music.
		Mix_FreeMusic(gMusic);
		Mix_FreeChunk(stun);
		stun = NULL;
		Mix_FreeChunk(lose);
		lose = NULL;
		Mix_FreeChunk(level_up);
		level_up = NULL;
		Mix_FreeChunk(item);
		item = NULL;
		gMusic = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
		Mix_Quit();
	}

}//end namespace GMUCS425
