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

	player_speed = 0.5f;

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

	App->collision->AddCollider({ 2854, 16, 134, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2854, 146, 134, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2833, 82, 21, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2833, 147, 21, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2836, 77, 18, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2836, 158, 18, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2841, 74, 13, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2841, 163, 13, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2849, 69, 5, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2849, 166, 5, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2844, 72, 5, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2844, 166, 5, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2834, 16, 20, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2834, 219, 20, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2836, 21, 3, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2836, 217, 3, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2839, 21, 15, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2839, 216, 15, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2844, 24, 10, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2844, 214, 10, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2849, 26, 5, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2849, 211, 5, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2852, 29, 2, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2852, 204, 2, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2988, 16, 18, 66 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2988, 158, 18, 66 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 16, 16, 48 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 176, 16, 48 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 64, 14, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 172, 14, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 68, 12, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 168, 12, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 72, 9, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 164, 9, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 76, 5, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 161, 5, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2988, 82, 11, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2988, 156, 11, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2949, 94, 11, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2949, 144, 11, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3022, 51, 2, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3022, 178, 2, 11 }, COLLIDER_WALL);


	App->collision->AddCollider({ 3152, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3152, 16, 64, 15 }, COLLIDER_WALL);

	App->collision->AddCollider({ 3472, 209, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3472, 16, 64, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3536, 193, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3536, 16, 64, 31 }, COLLIDER_WALL);

	//Add all enmies
	//Red
	
	App->enemy->AddEnemy(App->enemy->red, 410, 70, 'sin', 0.0f);
	App->enemy->AddEnemy(App->enemy->red, 420, 65, 'sin', (3.14f / 4.0f));
	App->enemy->AddEnemy(App->enemy->red, 430, 70, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 440, 65, 'sin', (3.14f));

	App->enemy->AddEnemy(App->enemy->red, 480, 170, 'sin', 0.0f);
	App->enemy->AddEnemy(App->enemy->red, 490, 180, 'sin', (3.14f / 4.0f));
	App->enemy->AddEnemy(App->enemy->red, 500, 170, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 510, 160, 'sin', (3.14f));

	// worm
	App->enemy->AddEnemy(App->enemy->worm, 580, 100, 'sin2', (0.0f));
	App->enemy->AddEnemy(App->enemy->worm, 585, 100, 'sin2', (3.14f / 32.0f));
	App->enemy->AddEnemy(App->enemy->worm, 590, 100, 'sin2', (3.14f / 16.0f));
	App->enemy->AddEnemy(App->enemy->worm, 595, 100, 'sin2', (3.14f / 32.0f));
	App->enemy->AddEnemy(App->enemy->worm, 600, 100, 'sin2', (0.0f));

	App->enemy->AddEnemy(App->enemy->worm, 650, 140, 'sin', (0.0f));
	App->enemy->AddEnemy(App->enemy->worm, 655, 140, 'sin', (3.14f / 16.0f));
	App->enemy->AddEnemy(App->enemy->worm, 660, 140, 'sin', (3.14f / 8.0f));
	App->enemy->AddEnemy(App->enemy->worm, 665, 140, 'sin', (3.14f / 16.0f));
	App->enemy->AddEnemy(App->enemy->worm, 670, 140, 'sin', (0.0f));
	
	//red
	App->enemy->AddEnemy(App->enemy->red, 750, 160, 'sin', 0.0f);
	App->enemy->AddEnemy(App->enemy->red, 760, 170, 'sin', (3.14f / 4.0f));
	App->enemy->AddEnemy(App->enemy->red, 770, 160, 'sin', (3.14f / 2.0f));

	App->enemy->AddEnemy(App->enemy->red, 840, 100, 'sin', 0.0f);
	App->enemy->AddEnemy(App->enemy->red, 850, 90, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 870, 65, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 880, 70, 'sin', 0.0f);

	App->enemy->AddEnemy(App->enemy->red, 900, 130, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 920, 65, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 930, 70, 'sin', 0.0f);

	App->enemy->AddEnemy(App->enemy->red, 950, 130, 'sin', (3.14f / 2.0f));

	App->enemy->AddEnemy(App->enemy->red, 970, 65, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 980, 65, 'sin', 0.0f);

	App->enemy->AddEnemy(App->enemy->red, 1000, 140, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 1010, 100, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 1030, 65, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 1040, 75, 'sin', (0.0f));
	App->enemy->AddEnemy(App->enemy->red, 1050, 50, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 1080, 130, 'sin', (3.14f / 2.0f));

	App->enemy->AddEnemy(App->enemy->red, 1100, 140, 'sin', (3.14f / 2.0f));
	App->enemy->AddEnemy(App->enemy->red, 1110, 130, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 1140, 80, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 1170, 50, 'sin', (3.14f / 4.0f));
	App->enemy->AddEnemy(App->enemy->red, 1190, 150, 'sin', (3.14f / 4.0f));

	App->enemy->AddEnemy(App->enemy->red, 1230, 50, 'sin', (0.0f));
	App->enemy->AddEnemy(App->enemy->red, 1240, 60, 'sin', (3.14f / 2.0f));


	App->enemy->AddEnemy(App->enemy->worm, 1300, 50, 'sin', (0.0f));
	App->enemy->AddEnemy(App->enemy->worm, 1305, 50, 'sin', (3.14f / 16.0f));
	App->enemy->AddEnemy(App->enemy->worm, 1310, 50, 'sin', (3.14f / 8.0f));
	App->enemy->AddEnemy(App->enemy->worm, 1315, 50, 'sin', (3.14f / 16.0f));
	App->enemy->AddEnemy(App->enemy->worm, 1320, 50, 'sin', (0.0f));

	App->enemy->AddEnemy(App->enemy->worm, 1400, 130, 'sin', (0.0f));

	//needed new type of mov
	//App->enemy->AddEnemy(App->enemy->worm, 1965, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 1965, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 1965, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 1965, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 1965, 130, 'sin', (0.0f));

	App->enemy->AddEnemy(App->enemy->red, 2400, 150, 'sin', (0.0f));
	App->enemy->AddEnemy(App->enemy->red, 2410, 160, 'sin', (3.14f / 2.0f));

	App->enemy->AddEnemy(App->enemy->red, 2520, 60, 'sin', (0.0f));

	App->enemy->AddEnemy(App->enemy->red, 2600, 120, 'sin', (0.0f));
	

	//needed new type of mov
	//App->enemy->AddEnemy(App->enemy->worm, 2670, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 2670, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 2670, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 2670, 130, 'sin', (0.0f));
	//App->enemy->AddEnemy(App->enemy->worm, 2670, 130, 'sin', (0.0f));



	//tryouts
	App->enemy->AddEnemy(App->enemy->worm, 1610, 140, 'bot', (0.0f));


	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->particles->CleanUpActiveParticles();
	App->enemy->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------

	App->player->position.x += player_speed;
	App->renderer->camera.x -= 1;

	if (App->renderer->camera.x == (-3930 + SCREEN_WIDTH)*SCREEN_SIZE)
	{
		App->player->speed = 0;
		App->fade->FadeToBlack(App->scene_space, App->scene_end, 2.0f);
	}
		

	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);

	return UPDATE_CONTINUE;
}
