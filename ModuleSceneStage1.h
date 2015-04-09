#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneStage1 : public Module
{
public:
	ModuleSceneStage1(Application* app, bool start_enabled = true);
	~ModuleSceneStage1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics;
	SDL_Rect background;


	float foreground_pos;
	bool forward;
};