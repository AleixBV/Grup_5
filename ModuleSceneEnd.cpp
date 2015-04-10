#include "Globals.h"
#include "Application.h"
#include "ModuleSceneEnd.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneEnd::ModuleSceneEnd(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	background = { 0, 0, 400, 200 };
}

ModuleSceneEnd::~ModuleSceneEnd()
{}

// Load assets
bool ModuleSceneEnd::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("End.png");
	App->player->Disable();

	return ret;
}

// Load assets
bool ModuleSceneEnd::CleanUp()
{
	LOG("Unloading End stage");

	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModuleSceneEnd::Update()
{
	// Draw everything --------------------------------------	

	App->renderer->Blit(graphics, (-3930 + SCREEN_WIDTH)*SCREEN_SIZE, 0, &background);

	return UPDATE_CONTINUE;
}