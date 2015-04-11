#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#include "List.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	Animation* current_animation;
	Animation still;
	Animation up;
	Animation down;
	Animation projectile_standard;
	p2Point<float> position;

	p2List<p2Point<float>> projectiles;
	p2Point<float> projectile;
};