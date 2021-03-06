#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleEnemy.h"

struct Collider;

class ModuleSceneSpace : public Module
{
public:
	ModuleSceneSpace(Application* app, bool start_enabled = true);
	~ModuleSceneSpace();

	bool Start();
	update_status Update();
	bool CleanUp();
	void BossIsDead();

public:
	
	SDL_Texture* background;
	SDL_Texture* stars;

	float player_speed;
	float camera_speed;
	
	bool boss_alive;
};