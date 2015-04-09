#include "Globals.h"
#include "Application.h"
#include "ModuleSceneStage1.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneStage1::ModuleSceneStage1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

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

	// Girl Animation
	girl.frames.PushBack({ 624, 16, 32, 56 });
	girl.frames.PushBack({ 624, 80, 32, 56 });
	girl.frames.PushBack({ 624, 144, 32, 56 });
	girl.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading ken scene");

	graphics = App->textures->Load("ken_stage.png");

	// TODO 1: Fer Enable/Disable del jugador i posar la musica

	return true;
}

// UnLoad assets
bool ModuleSceneStage1::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneStage1::Update()
{
	// Calculate boat Y position -----------------------------
	if (foreground_pos < -6.0f)
		forward = false;
	else if (foreground_pos > 0.0f)
		forward = true;

	if (forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky

	App->renderer->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	App->renderer->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation

	App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 3: Fer que al apretar el espai es façi un fade i es carregui HondaStage

	return UPDATE_CONTINUE;
}