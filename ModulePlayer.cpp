#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 100;
	position.y = 150;
	
	still.frames.PushBack({ 167, 1, 32, 16 });
	still.speed = 0.0f;


	//up animation
	up.frames.PushBack({ 200, 1, 32, 16 });
	up.frames.PushBack({ 232, 1, 32, 16 });
	up.speed = 0.1f;

	//down animation
	down.frames.PushBack({ 133, 1, 32, 16 });
	down.frames.PushBack({ 100, 1, 32, 16 });
	down.speed = 0.1f;

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
	Animation* current_animation = &still;
	// debug camera movement --------------------------------
	float speed = 0.75f;
	if (position.x < 900)
		position.x += speed;
	if(App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		if (position.x > 0)
			position.x -= 2*speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		if (position.x < 900)
			position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		
		if (position.y < 225) {
			current_animation = &down;
			position.y += speed;
		}

	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		
		if (position.y > 15) {
			position.y -= speed;
			current_animation = &up;
		}
	}


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}