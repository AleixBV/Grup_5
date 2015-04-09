#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneEnd : public Module
{
public:
	ModuleSceneEnd(Application* app, bool start_enabled = true);
	~ModuleSceneEnd();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect background;

};