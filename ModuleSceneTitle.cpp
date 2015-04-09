#include "Globals.h"
#include "Application.h"
#include "ModuleSceneTitle.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneTitle::ModuleSceneTitle(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	background = {0, 0, 400, 200};


	/*
	// ground
	ground = {8, 376, 848, 64};

	// roof
	roof = {91, 7, 765, 49};

	// foreground
	foreground = {164, 66, 336, 51};

	// Background / sky
	background = {120, 128, 671, 199};

	// flag animation
	water.frames.PushBack({8, 447, 283, 9});
	water.frames.PushBack({296, 447, 283, 12});
	water.frames.PushBack({588, 447, 283, 18});
	water.speed = 0.02f;
	*/
}

ModuleSceneTitle::~ModuleSceneTitle()
{}

// Load assets
bool ModuleSceneTitle::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("TitleProb.png");
	//App->audio->PlayMusic("honda.ogg", 1.0f);
	App->player->Disable();

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

	/*
	App->renderer->Blit(graphics, 0, 160, &ground);
	App->renderer->Blit(graphics, 50, -15, &background, 0.75f); // back of the room
	
	App->renderer->Blit(graphics, 280, 125, &foreground);
	App->renderer->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation
	App->renderer->Blit(graphics, 0, -16, &roof, 0.75f);
	*/

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(this, App->scene_stage1, 2.0f);

	return UPDATE_CONTINUE;
}