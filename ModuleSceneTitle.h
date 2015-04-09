#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneTitle : public Module
{
public:
	ModuleSceneTitle(Application* app, bool start_enabled = true);
	~ModuleSceneTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect background;

};