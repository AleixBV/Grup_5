#pragma once

#include "List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
<<<<<<< HEAD
//#include "ModuleAudio.h"
#include "ModuleSceneKen.h"
=======
#include "ModuleAudio.h"
#include "ModuleSceneStage1.h"
>>>>>>> origin/master
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHonda.h"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
<<<<<<< HEAD
//	ModuleAudio* audio;
	ModuleSceneKen* scene_ken;
=======
	ModuleAudio* audio;
	ModuleSceneStage1* scene_stage1;
>>>>>>> origin/master
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleSceneHonda* scene_honda;

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