#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

struct Enemy
{
	Animation anim;
	Animation death;
	p2Point<int> position;
	p2Point<int> speed;
	Collider* collider;
	Particle shoot;
	bool alive;
	bool on_screen;
	char mov_type;
	float fase;
	int initial_height;

	Enemy();
	~Enemy();
};

class ModuleEnemy : public Module
{
public:

	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	bool shooting;

	Enemy* AddEnemy(const Enemy& enemy, int x, int y, char mov, float fase);

private:

	SDL_Texture* graphics;
	p2List<Enemy*> EnemyList;

public:

	Enemy red;
	Enemy worm;
	Enemy tower;

};