#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 150;
	
	still.frames.PushBack({ 167, 1, 32, 16 });


	//up animation
	up.frames.PushBack({ 200, 1, 32, 16 });
	up.frames.PushBack({ 232, 1, 32, 16 });
	up.loop = false;
	up.speed = 0.5f;

	//down animation
	down.frames.PushBack({ 133, 1, 32, 16 });
	down.frames.PushBack({ 100, 1, 32, 16 });
	down.loop = false;
	down.speed = 0.5f;

	//projectile_standard
	projectile_standard.frames.PushBack({ 232, 100, 16, 16 });
	projectile_standard.frames.PushBack({ 248, 100, 16, 16 });
	projectile_standard.loop = true;
	projectile_standard.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ShipSprites_Alpha.png"); // arcade version

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
	float speed = 1.0f;

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		if (position.x > (App->renderer->camera.x)/-3)
			position.x -= 1.2*speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		if (position.x < (App->renderer->camera.x / -3)+ SCREEN_WIDTH - 32)
			position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		if (position.y < SCREEN_HEIGHT - 16)
		{
			position.y += speed;

			if (current_animation != &down)
			{
				down.Reset();
				current_animation = &down;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		if (position.y > 0)
		{
			position.y -= speed;
			if (current_animation != &up)
			{
				up.Reset();
				current_animation = &up;
			}
		}
	}


	if (App->input->keyboard[SDL_SCANCODE_S] == 0 && App->input->keyboard[SDL_SCANCODE_W] == 0)
		current_animation = &still;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		projectile.x = position.x + 32;
		projectile.y = position.y;
		projectiles.add(projectile);
	}

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	if (projectiles.getFirst() != NULL)
	{
		p2List_item<p2Point<float>>* tmp = projectiles.getFirst();

		while (tmp != NULL)
		{
			App->renderer->Blit(graphics, tmp->data.x, tmp->data.y, &(projectile_standard.GetCurrentFrame()));
			tmp = tmp->next;
		}

		delete tmp;
	}

	return UPDATE_CONTINUE;
}