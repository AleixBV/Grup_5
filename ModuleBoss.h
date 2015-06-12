#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

class BossTail
{
private:
	Animation end;
	SDL_Rect piece_frame [18];
	Collider* piece_collider [19];
	p2Point<int> position [19];
	Application* App;
	SDL_Texture* graphics;


public:

	BossTail(Application* app, SDL_Texture* texture);
	~BossTail();

	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);	
};

class ModuleBoss : public Module
{
public:

	ModuleBoss(Application* app, bool start_enabled = true);
	~ModuleBoss();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void Arrival();
	void Shooting();
	void Die();

private:

	Animation body;
	Animation eye[3];
	Animation baby;
	Animation baby_shot_before;
	Animation baby_shot_after;
	Animation shot;
	Animation death;
	p2Point<int> position;
	Collider* collider_skin_head;
	Collider* collider_skin_neck;
	Collider* collider_skin_bottom;
	Collider* collider_baby;
	Particle shoot;

	bool ship_is_here;
	bool can_shoot;
	int num_hits;
	BossTail* tail;

	SDL_Texture* graphics;

public:
	bool alive;
};