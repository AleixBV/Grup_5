#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include <math.h>

ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleEnemy::~ModuleEnemy()
{}

bool ModuleEnemy::Start()
{
	LOG("Loading enemies");
	graphics = App->textures->Load("rtype/Enemies_Sprites.png");

	red.anim.frames.PushBack({ 5, 6, 21, 24 });
	red.anim.frames.PushBack({ 38, 6, 21, 24 });
	red.anim.frames.PushBack({ 71, 6, 21, 24 });
	red.anim.frames.PushBack({ 104, 6, 21, 24 });
	red.anim.frames.PushBack({ 137, 6, 21, 24 });
	red.anim.frames.PushBack({ 170, 6, 21, 24 });
	red.anim.frames.PushBack({ 203, 6, 21, 24 });
	red.anim.frames.PushBack({ 236, 6, 21, 24 });
	red.anim.loop = true;
	red.anim.speed = 0.15f;
	red.alive = true;

	worm.anim.frames.PushBack({ 141, 37, 26, 22});
	worm.anim.frames.PushBack({ 171, 37, 26, 22 });
	worm.anim.frames.PushBack({ 204, 37, 26, 22 });
	worm.anim.frames.PushBack({ 238, 37, 26, 22 });
	worm.anim.frames.PushBack({ 270, 37, 26, 22 });
	worm.anim.frames.PushBack({ 238, 37, 26, 22 });
	worm.anim.frames.PushBack({ 303, 37, 26, 22 });
	worm.anim.frames.PushBack({ 337, 37, 26, 22 });
	worm.anim.frames.PushBack({ 371, 37, 26, 22 });
	worm.anim.frames.PushBack({ 141, 70, 26, 22 });
	worm.anim.frames.PushBack({ 173, 70, 26, 22 });
	worm.anim.frames.PushBack({ 205, 70, 26, 22 });
	worm.anim.frames.PushBack({ 237, 70, 26, 22 });
	worm.anim.frames.PushBack({ 270, 70, 26, 22 });
	worm.anim.frames.PushBack({ 304, 70, 26, 22 });
	worm.anim.frames.PushBack({ 336, 70, 26, 22 });
	worm.anim.frames.PushBack({ 369, 70, 26, 22 });
	worm.anim.loop = true;
	worm.anim.speed = 0.15f;
	worm.alive = true;

	return true;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);

	p2List_item<Enemy*>* item = EnemyList.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->prev;
	}

	EnemyList.clear();

	return true;
}

update_status ModuleEnemy::PreUpdate()
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();
	p2List_item<Enemy*>* tmp_next;
	while (tmp != NULL)
	{
		tmp_next = tmp->next;

		if (tmp->data->position.x < (App->renderer->camera.x / -3) + SCREEN_WIDTH)
		{
			tmp->data->on_screen = true;
		}

		/*if (tmp->data->alive == false)
		{
			EnemyList.del(tmp);
		}*/


		tmp = tmp_next;
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::Update()
{
	p2List_item<Enemy*>* tmp = EnemyList.getFirst();

	while (tmp != NULL)
	{
		Enemy* e = tmp->data;

		if (e->on_screen)
		{
			char x = 'sin';
			if (e->mov_type == x)
			{
				float t = SDL_GetTicks();
				e->position.y = e->initial_height + 25 * sin((25 + t / 250) + e->fase);
				e->position.x--;
			}
		}

		if (tmp->data->alive)
		{
			e->collider->rect.x = e->position.x;
			e->collider->rect.y = e->position.y;

			App->renderer->Blit(graphics, e->position.x, e->position.y, &(e->anim.GetCurrentFrame()));
			
			if (e->position.x == 550){
			
				if (e->position.y > App->player->position.y && e->position.x > App->player->position.x) 
				{
					App->particles->shot.speed.x = -2.5f;
					App->particles->shot.speed.y = -2.5f;
				}
				if (e->position.y > App->player->position.y && e->position.x < App->player->position.x)
				{
					App->particles->shot.speed.x = 2.5f;
					App->particles->shot.speed.y = -2.5f;
				}
				if (e->position.y < App->player->position.y && e->position.x > App->player->position.x)
				{
					App->particles->shot.speed.x = -2.5f;
					App->particles->shot.speed.y = 2.5f;
				}
				if (e->position.y < App->player->position.y && e->position.x < App->player->position.x)
				{
					App->particles->shot.speed.x = 2.5f;
					App->particles->shot.speed.y = 2.5f;
				}
		

				App->particles->AddParticle(App->particles->shot, e->position.x, e->position.y, COLLIDER_ENEMY_SHOT);
			}
		}

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
		if (e->on_screen)
		{
			if (c1 == e->collider || c2 == e->collider)
			{
				if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
				{
					e->alive = false;
					e->collider->to_delete = true;
					App->particles->AddParticle(App->particles->enemy_death, e->position.x, e->position.y);
				}
			}
		}
		tmp = tmp->next;
	}


}

Enemy* ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y, char mov, float fase)
{
	Enemy* e = new Enemy(enemy);
	e->position.x = x;
	e->position.y = y;
	e->fase = fase;
	e->initial_height = y;

	e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 21, 24 }, COLLIDER_ENEMY, this);

	e->mov_type = mov;

	EnemyList.add(e);

	return (e);
}

Enemy::Enemy() :collider(NULL), alive(true), on_screen(false)
{}

Enemy::~Enemy()
{
	if (collider)
	{
		collider->to_delete = true;
	}
}
