#include "Globals.h"
#include "Application.h"
#include "ModuleSceneContinue.h"

ModuleSceneContinue::ModuleSceneContinue(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx_continue = 0;
}

ModuleSceneContinue::~ModuleSceneContinue()
{}

// Load assets
bool ModuleSceneContinue::Start()
{
	LOG("Loading Continue assets");
	bool ret = true;
	fade_out == false;
	App->player->exploding = false;

	graphics = App->textures->Load("rtype/continue.png");
	fx_continue = App->audio->LoadFx("rtype/continue.ogg");
	App->audio->PlayMusic("rtype/Nothing.ogg", 0.0f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	time = SDL_GetTicks();

	App->audio->PlayFx(fx_continue);

	return ret;
}

// Load assets
bool ModuleSceneContinue::CleanUp()
{
	LOG("Unloading Continue scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneContinue::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && fade_out == false)
	{
		App->fade->FadeToBlack(this, App->scene_space, 3.0f);
		fade_out = true;
	}

	if (SDL_GetTicks() - time < 1000)//10
	{

	}
	else if (SDL_GetTicks() - time < 2000)//9
	{

	}
	else if (SDL_GetTicks() - time < 3000)//8
	{

	}
	else if (SDL_GetTicks() - time < 4000)//7
	{

	}
	else if (SDL_GetTicks() - time < 5000)//6
	{

	}
	else if (SDL_GetTicks() - time < 6000)//5
	{

	}
	else if (SDL_GetTicks() - time < 7000)//4
	{

	}
	else if (SDL_GetTicks() - time < 8000)//3
	{

	}
	else if (SDL_GetTicks() - time < 9000)//2
	{

	}
	else if (SDL_GetTicks() - time < 10000)//1
	{

	}
	else if (SDL_GetTicks() - time < 11000)//0
	{

	}
	else if (SDL_GetTicks() - time < 12000)
	{
		App->fade->FadeToBlack(App->scene_continue, App->scene_intro);
	}

	return UPDATE_CONTINUE;
}