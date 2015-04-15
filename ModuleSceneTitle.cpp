#include "Globals.h"
#include "Application.h"
#include "ModuleSceneTitle.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneTitle::ModuleSceneTitle(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	background = {0, 0, 400, 200};
}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	App->player->has_collided = false;

	graphics = App->textures->Load("TitleProb.png");
	App->audio->PlayMusic("Title.ogg", 1.0f);
	App->player->Disable();
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading title stage");

	App->textures->Unload(graphics);
	

	return true;
}

// Update: draw background
update_status ModuleSceneTitle::Update()
{
	// Draw everything --------------------------------------	

	App->renderer->Blit(graphics, 0, 0, &background);

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		App->fade->FadeToBlack(this, App->scene_stage1, 2.0f);

	return UPDATE_CONTINUE;
}