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
	bool onScreen;

	Enemy();
	~Enemy();
};

class ModuleEnemy : public Module
{
public:

	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status preUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	void AddEnemy(const Enemy& enemy, int x, int y);

private:

	SDL_Texture* graphics;
	p2List<Enemy*> EnemyList;

public:

	Enemy red;

};