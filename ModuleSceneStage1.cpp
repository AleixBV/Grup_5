#include "Globals.h"
#include "Application.h"
#include "ModuleSceneStage1.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneStage1::ModuleSceneStage1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	background = { 0, 0, 1782, 600 };
	/*
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.PushBack({848, 208, 40, 40});
	flag.frames.PushBack({848, 256, 40, 40});
	flag.frames.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.frames.PushBack({624, 16, 32, 56});
	girl.frames.PushBack({624, 80, 32, 56});
	girl.frames.PushBack({624, 144, 32, 56});
	girl.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
	*/
}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("Background3.png");
//	App->audio->PlayMusic("ken.ogg", 1.0f);
	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneStage1::CleanUp()
{
	LOG("Unloading stage scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneStage1::Update()
{

	App->renderer->Blit(graphics, background.x, 0, &background);

	unsigned int speed = 2;
	App->scene_stage1->background.x -= speed;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(this, App->scene_end, 2.0f);


		

	return UPDATE_CONTINUE;
}