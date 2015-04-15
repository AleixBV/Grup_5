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

	void OnCollision(Collider*, Collider*);

public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	Animation still;
	Animation up;
	Animation down;
	Animation explosion;
	p2Point<int> position;

	bool has_collided;

	int speed = 1;
};