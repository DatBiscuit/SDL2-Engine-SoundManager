#include <time.h>
#include "Rendering.h"

//Game loop rate variables
const int FRAME_RATE = 100;
const int FRAMES_TO_SKIP = 1000 / FRAME_RATE;
const int MAX_FRAME_SKIP = 10;

Rendering rendering;

//Initialize screen and SDL/SDL_image systems
bool InitializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_image could not initialize. Error: " << IMG_GetError() << std::endl;
		return false;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize. Error: " << TTF_GetError() << std::endl;
		return false;
	}

	return rendering.Init();
}

bool HandleInput(SDL_Event *e)
{
	while (SDL_PollEvent(e) != 0) { if (e->type == SDL_QUIT) { return false; } }
	return true;
}

void Render()
{
	SDL_RenderClear(rendering.renderer);

    /*while(!rendering.renderQueue.empty())
	{
		rendering.Render(rendering.renderQueue.top());
		rendering.renderQueue.pop();
	}*/

	SDL_RenderPresent(rendering.renderer);
}

bool TerminateSDL()
{
	SDL_DestroyRenderer(rendering.renderer);
	SDL_DestroyWindow(rendering.window);
	rendering.window = NULL;
	rendering.renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return true;
}

int main(int argc, char *args[])
{
	if (!InitializeSDL()) { return 1; }

	std::cout << "Soccer With Guns" << std::endl;
	std::cout << std::endl;
	std::cout << "It's soccer, but with guns" << std::endl;
	std::cout << std::endl;

	//Game loop variables
	srand((unsigned int)time(NULL));
	Uint32 next_game_tick = SDL_GetTicks();
	int loops = 0;
	bool inGame = true;

	//SDL specific members
	SDL_Event e;

	while (inGame)
	{
		loops = 0;
		while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAME_SKIP)
		{
			next_game_tick += FRAMES_TO_SKIP;
			++loops;
			inGame = HandleInput(&e);
			if (!inGame) { break; }
			
			//Start Game logic 
		}
		if (loops > 1) { std::cout << "LAG: " << loops - 1 << std::endl; }
	}

	if (!TerminateSDL()) { return 1; }
	return 0;
}