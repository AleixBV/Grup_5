#include "Globals.h"
#include "Application.h"
#include "ModuleSceneSpace.h"

ModuleSceneSpace::ModuleSceneSpace(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	stars = NULL;
}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("rtype/background.png");

	player_speed = 1;

	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	App->collision->AddCollider({0,224,3930, 16}, COLLIDER_WALL);
	App->collision->AddCollider({ 142, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 206, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 592, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 720, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1232, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1376, 0, 560, 16 }, COLLIDER_WALL);//paret de dalt
	
	App->collision->AddCollider({ 1376, 16, 110, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1376, 144, 110, 80 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2000, 0, 640, 16 }, COLLIDER_WALL);//paret de dalt
	App->collision->AddCollider({ 2704, 0, 1226, 16 }, COLLIDER_WALL);//paret de dalt

	// TODO 1: Afegir colliders a les primeres columnes del nivell

    App->enemy->AddEnemy(red, 600, 100);
	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------

	if (App->renderer->camera.x >= (-3930 + SCREEN_WIDTH)*SCREEN_SIZE)
	{
		App->player->position.x += player_speed;
		App->renderer->camera.x -= 3;
	}
	//else
		//App->fade->FadeToBlack(this, App->scene_end, 2.0f);
	
	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}
