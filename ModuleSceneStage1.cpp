#include "Globals.h"
#include "Application.h"
#include "ModuleSceneStage1.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneStage1::ModuleSceneStage1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	background = { 0, 0, 1782, 600 };
}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("lvl1.png");
	App->audio->PlayMusic("stage1.ogg", 1.0f);
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

	App->renderer->Blit(graphics, 0, 0, &background);

	unsigned int speed = 2;
	App->renderer->background.x -= speed;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(this, App->scene_end, 2.0f);


		

	return UPDATE_CONTINUE;
}