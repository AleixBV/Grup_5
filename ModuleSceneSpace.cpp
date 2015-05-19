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
	App->enemy->Enable();
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Add WALL COLLIDERS

	App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);//paret de baix
	App->collision->AddCollider({ 142, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 206, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 592, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 720, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1232, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1376, 0, 560, 16 }, COLLIDER_WALL);//paret de dalt

	App->collision->AddCollider({ 1378, 16, 4, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1378, 221, 4, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1382, 16, 4, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1382, 218, 4, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1386, 16, 3, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1386, 216, 3, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1389, 16, 3, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1389, 214, 3, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1392, 16, 3, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1392, 213, 3, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1395, 16, 3, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1395, 210, 3, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1398, 16, 2, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1398, 208, 2, 16 }, COLLIDER_WALL);

	App->collision->AddCollider({ 1377, 57, 23, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1377, 153, 23, 30 }, COLLIDER_WALL);

	App->collision->AddCollider({ 1395, 87, 5, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1395, 146, 5, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1392, 87, 3, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1392, 150, 3, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1395, 50, 5, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1395, 183, 5, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1392, 54, 3, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1392, 183, 3, 3 }, COLLIDER_WALL);

	App->collision->AddCollider({ 1400, 16, 74, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1400, 144, 74, 80 }, COLLIDER_WALL);

	App->collision->AddCollider({ 1744, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1680, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1744, 16, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1680, 16, 64, 15 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2000, 0, 640, 16 }, COLLIDER_WALL);//paret de dalt

	App->collision->AddCollider({ 2064, 201, 16, 23 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2064, 16, 16, 23 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2080, 206, 4, 18 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2080, 16, 4, 18 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2084, 208, 4, 16 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2084, 16, 4, 16 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2088, 210, 4, 14 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2088, 16, 4, 14 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2092, 212, 4, 12 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2092, 16, 4, 12 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2096, 214, 4, 10 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2096, 16, 4, 10 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2100, 216, 4, 8 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2100, 16, 4, 8 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2104, 218, 4, 6 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2104, 16, 4, 6 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2108, 220, 6, 4 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2108, 16, 6, 4 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2114, 222, 6, 2 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2114, 16, 6, 2 }, COLLIDER_WALL);//rodona

	App->collision->AddCollider({ 2200, 222, 6, 2 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2200, 16, 6, 2 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2206, 220, 6, 4 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2206, 16, 6, 4 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2212, 218, 4, 6 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2212, 16, 4, 6 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2216, 216, 4, 8 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2216, 16, 4, 8 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2220, 214, 4, 10 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2220, 16, 4, 10 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2224, 212, 4, 12 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2224, 16, 4, 12 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2228, 210, 4, 14 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2228, 16, 4, 14 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2232, 208, 4, 16 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2232, 16, 4, 16 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2236, 206, 4, 18 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2236, 16, 4, 18 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2240, 201, 16, 23 }, COLLIDER_WALL);//rodona
	App->collision->AddCollider({ 2240, 16, 16, 23 }, COLLIDER_WALL);//rodona

	App->collision->AddCollider({ 2384, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2384, 16, 64, 15 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2640, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2704, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2704, 16, 64, 31 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2704, 0, 1226, 16 }, COLLIDER_WALL);//paret de dalt

	App->collision->AddCollider({ 2854, 16, 168, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2854, 144, 168, 78 }, COLLIDER_WALL);

	App->collision->AddCollider({ 3152, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3152, 16, 64, 15 }, COLLIDER_WALL);

	App->collision->AddCollider({ 3472, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3472, 16, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3536, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3536, 16, 64, 31 }, COLLIDER_WALL);

	//Add all enmies
	//Red
	App->enemy->AddEnemy(App->enemy->red, 440, 70, 'sin', 0.0f);
	App->enemy->AddEnemy(App->enemy->red, 455, 65, 'sin', (3.14f / 4.0f));
	App->enemy->AddEnemy(App->enemy->red, 470, 70, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 485, 65, 'sin', (3.14f));

	App->enemy->AddEnemy(App->enemy->red, 550, 170, 'sin', 0.0f);
	App->enemy->AddEnemy(App->enemy->red, 567, 180, 'sin', (3.14f / 4.0f));
	App->enemy->AddEnemy(App->enemy->red, 584, 170, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 600, 160, 'sin', (3.14f));

	App->enemy->AddEnemy(App->enemy->worm, 550, 100, 'sin', (0.0f));

	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->enemy->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------

	App->player->position.x += player_speed;
	App->renderer->camera.x -= 3;

	if (App->renderer->camera.x == (-3930 + SCREEN_WIDTH)*SCREEN_SIZE)
	{
		App->player->speed = 0;
		App->fade->FadeToBlack(App->scene_space, App->scene_end, 2.0f);
	}
		

	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);

	return UPDATE_CONTINUE;
}
