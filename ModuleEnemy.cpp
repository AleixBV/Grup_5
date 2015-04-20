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

	//Add all enemies
	AddEnemy(red, 600, 100, COLLIDER_ENEMY);

	return true;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleEnemy::preUpdate()
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();
	while (tmp != NULL)
	{
		if (tmp->data->alive == false)
		{
			EnemyList.del(tmp);
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::Update()
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();
	p2List_item<Enemy*>* tmp_next = EnemyList.getFirst();

	while (tmp != NULL)
	{
		Enemy* e = tmp->data;
		if (tmp->data->alive != false)
		{
			App->renderer->Blit(graphics, e->position.x, e->position.y, &(e->anim.GetCurrentFrame()));
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();

	Enemy* e = tmp->data;

	if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
	{
		e->alive = false;
		App->particles->AddParticle(App->particles->enemy_death, e->position.x, e->position.y);
	}
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