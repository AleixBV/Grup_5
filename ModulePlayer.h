#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	Animation idle;
	Animation up;
	Animation down;
	Animation explosion;
	p2Point<int> position;

	bool exploding;

	int speed = 1;
};