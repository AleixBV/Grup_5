#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneContinue : public Module
{
public:
	ModuleSceneContinue(Application* app, bool start_enabled = true);
	~ModuleSceneContinue();

	bool Start();
	update_status Update();
	bool CleanUp();
	unsigned int time;

public:

	SDL_Texture* graphics;
	bool fade_out;
	unsigned int fx_continue;
};