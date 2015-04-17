#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"


ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleEnemy::~ModuleEnemy()
{}

bool ModuleEnemy::Start()
{
	LOG("Loading enemies");
	graphics = App->textures->Load("rtype/RedEnemySprites.png");

	red.anim.frames.PushBack({ 5, 6, 21, 24 });
	red.anim.loop = false;
	red.anim.speed = 0.0f;

	return true;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleEnemy::Update()
{

	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	//Segons el tipus de colisio el resultat sera diferent
}

void ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y, COLLIDER_TYPE collider_type)
{
	Enemy* e = new Enemy(enemy);
	e->position.x = x;
	e->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 0, 0 }, collider_type, this);
	}

	EnemyList.add(e);
}