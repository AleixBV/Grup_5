#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define DELAY_TIME 200;

enum player_states
{
	PLAYER_IDLE,
	PLAYER_UP,
	PLAYER_UPUP,
	PLAYER_DOWN,
	PLAYER_DOWNDOWN
};

enum player_inputs
{
	PLAYER_INPUT_IDLE,
	PLAYER_INPUT_UP,
	PLAYER_INPUT_DOWN,
};


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	player_states player_state;
	player_inputs player_input;

	void OnCollision(Collider*, Collider*);
	void Fsm();
	Uint32 delay_time;

public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	Animation idle;
	Animation up;
	Animation upup;
	Animation down;
	Animation downdown;
	Animation explosion;
	p2Point<int> position;

	bool exploding;

	int speed = 1;
};