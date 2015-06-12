#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneContinue.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"
#include "ModuleSceneEnd.h"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneSpace* scene_space;
	ModuleSceneContinue* scene_continue;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleSceneIntro* scene_intro;
	ModuleSceneEnd* scene_end;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleEnemy* enemy;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};