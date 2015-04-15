#include "Globals.h"
#include "Application.h"
#include "ModuleSceneStage1.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneStage1::ModuleSceneStage1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading ken scene");
	
	background = App->textures->Load("lvl1.png");

	player_speed = 1;

	App->collision->Enable();
	App->audio->PlayMusic("stage1.ogg", 1.0f);
	App->player->Enable();

	App->renderer->camera.x = App->renderer->camera.y = 0;

	App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1376, 16, 110, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1376, 144, 110, 80 }, COLLIDER_WALL);
	
	return true;
}

// UnLoad assets
bool ModuleSceneStage1::CleanUp()
{
	LOG("Unloading stage scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneStage1::Update()
{

	float scroll_speed = 0.75f;

	if (App->renderer->camera.x >= (-3930 + SCREEN_WIDTH)*SCREEN_SIZE)
	{
		App->player->position.x += player_speed;
		App->renderer->camera.x -= 3;
	}
	else
		App->fade->FadeToBlack(this, App->scene_end, 2.0f);


	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);

	return UPDATE_CONTINUE;
}