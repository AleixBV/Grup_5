#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

#define DELAY_TIME 200;


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;
	current_animation = NULL;

	// idle animation (just the ship)
	idle.frames.PushBack({66, 1, 32, 14});

	// move upwards
	up.frames.PushBack({100, 1, 32, 14});
	up.loop = false;
	up.speed = 0.0f;

	upup.frames.PushBack({132, 0, 32, 14});
	upup.loop = false;
	upup.speed = 0.0f;
	
	// Move down
	down.frames.PushBack({33, 1, 32, 14});
	down.loop = false;
	down.speed = 0.0f;

	downdown.frames.PushBack({ 0, 1, 32, 14 });
	downdown.loop = false;
	downdown.speed = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/ship.png");

	position.x = 120;
	position.y = 100;

	speed = 1;
	player_state = PLAYER_IDLE;
	Uint32 delay_time = 0;

	// TODO 2: Afegir collider al jugador
	collider = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	player_input = PLAYER_INPUT_IDLE;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (position.x > (App->renderer->camera.x) / -3)
			position.x -= 1.2*speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (position.x < (App->renderer->camera.x / -3) + SCREEN_WIDTH - 32)
			position.x += speed;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (position.y < SCREEN_HEIGHT - 16)
		{
			position.y += speed;

			player_input = PLAYER_INPUT_DOWN;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (position.y > 0)
		{
			position.y -= speed;

			player_input = PLAYER_INPUT_UP;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
	{
		player_input = PLAYER_INPUT_IDLE;
	}

	collider->rect.x = position.x;
	collider->rect.y = position.y;

	Fsm();

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 4: Detectar colisio del jugador y retornar a la pantalla de inici

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (exploding == false)
	{
		App->fade->FadeToBlack(App->scene_space, App->scene_intro);
		exploding = true;
		speed = 0;
		App->scene_space->player_speed = 0;
		CleanUp();
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	}
}

void ModulePlayer::Fsm()
{
	if (delay_time > 0)
	{
		if (SDL_GetTicks() - delay_time > 200/*DELAY_TIME*/)
		{
			delay_time = 0;
		}
	}

	if (delay_time == 0)
	{
		switch (player_state)
			{
		case PLAYER_IDLE:
		{
							current_animation = &idle;

							switch (player_input)
							{
							case PLAYER_INPUT_IDLE:
								break;
							case PLAYER_INPUT_UP: player_state = PLAYER_UP; delay_time = SDL_GetTicks();
								break;
							case PLAYER_INPUT_DOWN: player_state = PLAYER_DOWN; delay_time = SDL_GetTicks();
								break;
							default:
								break;
							}
		}
			break;

		case PLAYER_UP:
		{
						  current_animation = &up;

						  switch (player_input)
						  {
						  case PLAYER_INPUT_IDLE: player_state = PLAYER_IDLE; delay_time = SDL_GetTicks();
							  break;
						  case PLAYER_INPUT_UP: player_state = PLAYER_UPUP; delay_time = SDL_GetTicks();
							  break;
						  case PLAYER_INPUT_DOWN: player_state = PLAYER_IDLE; delay_time = SDL_GetTicks();
							  break;
						  default:
							  break;
						  }
		}
			break;

		case PLAYER_UPUP:
		{
							current_animation = &upup;
							switch (player_input)
							{
							case PLAYER_INPUT_IDLE: player_state = PLAYER_UP; delay_time = SDL_GetTicks();
								break;
							case PLAYER_INPUT_UP: player_state = PLAYER_UPUP; delay_time = SDL_GetTicks();
								break;
							case PLAYER_INPUT_DOWN: player_state = PLAYER_UP; delay_time = SDL_GetTicks();
								break;
							default:
								break;
							}
		}
			break;

		case PLAYER_DOWN:
		{
							current_animation = &down;
							switch (player_input)
							{
							case PLAYER_INPUT_IDLE: player_state = PLAYER_IDLE; delay_time = SDL_GetTicks();
								break;
							case PLAYER_INPUT_UP: player_state = PLAYER_IDLE; delay_time = SDL_GetTicks();
								break;
							case PLAYER_INPUT_DOWN: player_state = PLAYER_DOWNDOWN; delay_time = SDL_GetTicks();
								break;
							default:
								break;
							}
		}
			break;

		case PLAYER_DOWNDOWN:
		{
								current_animation = &downdown;
								switch (player_input)
								{
								case PLAYER_INPUT_IDLE: player_state = PLAYER_DOWN; delay_time = SDL_GetTicks();
									break;
								case PLAYER_INPUT_UP: player_state = PLAYER_DOWN; delay_time = SDL_GetTicks();
									break;
								case PLAYER_INPUT_DOWN: player_state = PLAYER_DOWNDOWN; delay_time = SDL_GetTicks();
									break;
								default:
									break;
								}
		}
			break;

		}
	}
}