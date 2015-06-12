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
	//fx_continue = App->audio->LoadFx("rtype/continue.ogg");
	fx_continue = App->audio->LoadFx("rtype/continue.wav");
	App->audio->PlayMusic("rtype/Nothing.ogg", 0.0f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	time = SDL_GetTicks();

	App->audio->PlayFx(fx_continue);

	App->particles->AddParticle(App->particles->numbers, SCREEN_WIDTH / 2 - 24, SCREEN_HEIGHT / 2 - 35);

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

	if (SDL_GetTicks() - time < 12000)
	{
		App->fade->FadeToBlack(App->scene_continue, App->scene_intro, 1.0f);
	}

	return UPDATE_CONTINUE;
}