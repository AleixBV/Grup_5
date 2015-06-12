#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Particle
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	bool follow_player;
	bool bounceT = false;
	bool bounceB = false;
	bool bounceR = false;
	bool bounceL = false;
	unsigned int lifes;
	Collider* collider;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool CleanUpActiveParticles();
	void OnCollision(Collider*, Collider*);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics;
	//SDL_Texture* enemy_explosion;
	p2List<Particle*> active;

public:

	Particle explosion;
	Particle enemy_death;
	Particle laser;
	Particle laser_anim;
	Particle laser_explosion;
	Particle laser_charged1;
	Particle laser_charged2;
	Particle laser_charged3;
	Particle laser_charged4;
	Particle laser_charged5;
	Particle laser_charged_anim;
	Particle laser_charged_explosion;
	Particle shot;
	Particle power_up;
	Particle laser_powerup;
	Particle laser_powerup_anim;
	Particle laser_blue;
	Particle laser_blue2;
	Particle laser_blue3;

};