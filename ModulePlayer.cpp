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
	still.speed = 0.0f;


	//up animation
	up.frames.PushBack({ 200, 1, 32, 16 });
	up.frames.PushBack({ 232, 1, 32, 16 });
	up.speed = 0.2f;
	up.loop = false;

	//down animation
	down.frames.PushBack({ 133, 1, 32, 16 });
	down.frames.PushBack({ 100, 1, 32, 16 });
	down.speed = 0.2f;
	down.loop = false;

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
	float speed = 0.75f;
	position.x += speed;
	if(App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		if (position.x > 0)
			position.x -= 2*speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		position.y += speed;
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		position.y -= speed;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	/*if (App->input->keyboard_down[SDL_SCANCODE_B] == 1)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
		App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 500);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 1000);
		App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 1500);
	}*/

	if (App->input->keyboard[SDL_SCANCODE_S] == 0 && App->input->keyboard[SDL_SCANCODE_W] == 0)
		current_animation = &still;


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}