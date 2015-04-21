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
	red.anim.loop = true;
	red.anim.speed = 0.0f;
	red.alive = true;

	//Add all enemies
	//AddEnemy(red, 600, 100); //al module stage

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
		tmp = tmp->next;
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::Update()
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();

	while (tmp != NULL)
	{
		Enemy* e = tmp->data;
		if (tmp->data->alive != false)
		{
			App->renderer->Blit(graphics, e->position.x, e->position.y, &(e->anim.GetCurrentFrame()));
		}

		e->collider->rect.x = e->position.x;
		e->collider->rect.y = e->position.y;

		tmp = tmp->next;
	}
	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();

   while (tmp != NULL)
	{
		Enemy* e = tmp->data;
		if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
    	{
		e->alive = false;
		e->collider->to_delete = true;
		App->particles->AddParticle(App->particles->enemy_death, e->position.x, e->position.y);
    	}
		tmp = tmp->next;
	}
	

}

void ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y)
{
	Enemy* e = new Enemy(enemy);
	e->position.x = x;
	e->position.y = y;
	
	e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 21, 24 }, COLLIDER_ENEMY, this);

	EnemyList.add(e);
}

Enemy::Enemy() :collider(NULL), alive(true), onScreen(false)
{}

Enemy::~Enemy()
{
	if (collider)
	{
		collider->to_delete = true;
	}
}
