//---------------------------------------------------------------
//  Include SDL headers and libs
//---------------------------------------------------------------
#include <stdlib.h>

#include "SDL\include\SDL.h"
#include "SDL_image\include\SDL_image.h"
#include "SDL_mixer\include\SDL_mixer.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

//---------------------------------------------------------------
//  Global vars
//---------------------------------------------------------------


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGTH 720

struct globals
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* background;

};

globals g;

//---------------------------------------------------------------
//---------------------------------------------------------------
void Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	g.window = SDL_CreateWindow(
		"Super Awesome Mega Cool",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGTH,
		SDL_WINDOW_SHOWN);


	g.renderer = SDL_CreateRenderer(g.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_PNG);
	g.background = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("background.png"));
}

//---------------------------------------------------------------
//---------------------------------------------------------------
void End()
{
	IMG_Quit();
	SDL_DestroyRenderer(g.renderer);
	SDL_DestroyWindow(g.window);
	SDL_Quit();

}

//---------------------------------------------------------------
//---------------------------------------------------------------
bool Input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_ESCAPE)
				return false;
		}
	}

	return true;
}

//---------------------------------------------------------------
//---------------------------------------------------------------
void MoveStuff()
{


}

//---------------------------------------------------------------
//---------------------------------------------------------------
void Render()
{
	SDL_RenderClear(g.renderer);

	SDL_RenderCopy(g.renderer, g.background, NULL, NULL);

	SDL_RenderPresent(g.renderer);
}


//---------------------------------------------------------------
//---------------------------------------------------------------
int main(int argc, char* argv)
{
	Init();

	while (Input())
	{
		MoveStuff();
		Render();
	}
	
	End();

	return(EXIT_SUCCESS);
}