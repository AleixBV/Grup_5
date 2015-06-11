#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include <math.h>
#include <ctime>
#include <stdio.h>

ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	red.type = _RED;
	worm.type = _WORM;
	tower.type = _TOWER;
	tower2.type = _TOWER2;
	robot.type = _ROBOT;
}

ModuleEnemy::~ModuleEnemy()
{}

bool ModuleEnemy::Start()
{
	shooting = true;

	LOG("Loading enemies");
	graphics = App->textures->Load("rtype/AllEnemies.png");

	red.anim.frames.PushBack({ 0, 0, 21, 24 });
	red.anim.frames.PushBack({ 33, 0, 21, 24 });
	red.anim.frames.PushBack({ 66, 0, 21, 24 });
	red.anim.frames.PushBack({ 99, 0, 21, 24 });
	red.anim.frames.PushBack({ 132, 0, 21, 24 });
	red.anim.frames.PushBack({ 165, 0, 21, 24 });
	red.anim.frames.PushBack({ 198, 0, 21, 24 });
	red.anim.frames.PushBack({ 231, 0, 21, 24 });
	red.anim.loop = true;
	red.anim.speed = 0.15f;
	red.alive = true;

	/*worm.anim.frames.PushBack({ 136, 31, 26, 22});
	worm.anim.frames.PushBack({ 166, 31, 26, 22 });
	worm.anim.frames.PushBack({ 199, 31, 26, 22 });
	worm.anim.frames.PushBack({ 233, 31, 26, 22 });*/

	worm.anim.frames.PushBack({ 265, 64, 26, 22 }); // amunt
	worm.anim.frames.PushBack({ 232, 64, 26, 22 });
	worm.anim.frames.PushBack({ 200, 64, 26, 22 });
	worm.anim.frames.PushBack({ 168, 64, 26, 22 });
	worm.anim.frames.PushBack({ 136, 64, 26, 22 }); // pla
	worm.anim.frames.PushBack({ 364, 31, 26, 22 });
	worm.anim.frames.PushBack({ 332, 31, 26, 22 });
	worm.anim.frames.PushBack({ 298, 31, 26, 22 });
	worm.anim.frames.PushBack({ 265, 31, 26, 22 }); // avall
	worm.anim.frames.PushBack({ 298, 31, 26, 22 });
	worm.anim.frames.PushBack({ 332, 31, 26, 22 });
	worm.anim.frames.PushBack({ 364, 31, 26, 22 });
	worm.anim.frames.PushBack({ 136, 64, 26, 22 }); // pla
	worm.anim.frames.PushBack({ 168, 64, 26, 22 });
	worm.anim.frames.PushBack({ 200, 64, 26, 22 });
	worm.anim.frames.PushBack({ 232, 64, 26, 22 });
	worm.anim.frames.PushBack({ 265, 64, 26, 22 }); // amunt

	/*worm.anim.frames.PushBack({ 265, 64, 26, 22 });
	worm.anim.frames.PushBack({ 299, 64, 26, 22 });
	worm.anim.frames.PushBack({ 331, 64, 26, 22 });
	worm.anim.frames.PushBack({ 364, 64, 26, 22 });*/
	worm.anim.loop = true;
	worm.anim.speed = 0.0f;
	worm.alive = true;

	tower2.anim.frames.PushBack({ 210, 90, 16, 16}); //left top
	tower2.anim.frames.PushBack({ 228, 90, 16, 16 }); //left/top top
	tower2.anim.frames.PushBack({ 245, 90, 16, 16 }); // top top l
	tower2.anim.frames.PushBack({ 262, 90, 16, 16 }); // top top r
	tower2.anim.frames.PushBack({ 279, 90, 16, 16 }); //right/top top
	tower2.anim.frames.PushBack({ 296, 90, 16, 16 }); //right top
	tower2.anim.loop = false;
	tower2.anim.speed = 0.0f;
	tower2.alive = true;

	tower.anim.frames.PushBack({ 210, 107, 16, 16 }); //left bot
	tower.anim.frames.PushBack({ 228, 107, 16, 16 }); //left/bot bot
	tower.anim.frames.PushBack({ 245, 107, 16, 16 }); // bot bot l
	tower.anim.frames.PushBack({ 262, 107, 16, 16 }); // bot bot r
	tower.anim.frames.PushBack({ 279, 107, 16, 16 }); //right/bot bot
	tower.anim.frames.PushBack({ 296, 107, 16, 16 }); //right bot

	tower.anim.loop = false;
	tower.anim.speed = 0.0f;
	tower.alive = true;


	robot.anim.frames.PushBack({ 162, 297, 32, 32 });//RW //0
	robot.anim.frames.PushBack({ 195, 297, 32, 32 }); // 1
	robot.anim.frames.PushBack({ 230, 297, 32, 32 }); // 2
	robot.anim.frames.PushBack({ 164, 330, 32, 32 });//RF // 3
	robot.anim.frames.PushBack({ 195, 330, 32, 32 }); // 4
	robot.anim.frames.PushBack({ 228, 330, 32, 32 }); // 5

	robot.anim.frames.PushBack({ 264, 297, 32, 32 });//LW // 6
	robot.anim.frames.PushBack({ 295, 297, 32, 32 }); // 7
	robot.anim.frames.PushBack({ 328, 297, 32, 32 }); // 8
	robot.anim.frames.PushBack({ 262, 330, 32, 32 });//LF // 9
	robot.anim.frames.PushBack({ 195, 330, 32, 32 }); // 10
	robot.anim.frames.PushBack({ 230, 330, 32, 32 }); // 11
	robot.anim.loop = true;
	robot.anim.speed = 0.0f;
	robot.alive = true;
	

	return true;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);

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

		if (tmp->data->position.x < (App->renderer->camera.x / -3) + SCREEN_WIDTH && tmp->data->position.x > (App->renderer->camera.x / -3))
		{
			tmp->data->on_screen = true;
		}
		
		else if (tmp->data->position.x < (App->renderer->camera.x / -3) - 250)
		{
			tmp->data->on_screen = false;
		}

		if (tmp->data->alive == false)
		{
			EnemyList.del(tmp);
		}


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
		SDL_Rect * frame = & e->anim.GetCurrentFrame();

		if (e->on_screen)
		{
			switch (e->mov_type)
			{
				case eSin:
				{
					float t = SDL_GetTicks();
					e->position.y = e->initial_height + 25 * sin(t / 250 + e->fase);
					e->position.x--;

					switch(e->type)
					{
						case _RED:
						{
							break;
						}

						case _WORM:
						{
							unsigned int frame_num;
							frame_num = (int)(e->fase * 3.82f + t / 104.72f + 7.5f) % 15;
							frame = &e->anim.frames[frame_num];
							break;
						}

						case _TOWER:
						{
							break;
						}
						case _TOWER2:
						{
							break;
						}

						case _ROBOT:
						{
							break;
						}
			
					}
					break;
				}

				case eSin2:
				{
					float t = SDL_GetTicks();
					e->position.y = e->initial_height + 30 * sin(t / 1000 + e->fase);
					e->position.x--;
					
					switch (e->type)
					{

					case _RED:
					{
						break;
					}

					case _WORM:
					{
						unsigned int frame_num = 0;
						frame_num = (int)(e->fase * 3.82f + t / 418.9f + 7.5f) % 15;
						frame = &e->anim.frames[frame_num];
						break;
					}

					case _TOWER:
					{
						break;
					}
					case _TOWER2:
					{
						break;
					}

					case _ROBOT:
					{
						break;
					}

					}

					break;
				}

				case eBot:
				{
					if (e->floor == false) 
						e->position.y++;

					else if (e->floor == true && e->right == true) 
						e->position.x++;

					else if (e->floor == true && e->right == false) 
						e->position.x--;

										
					switch (e->type)
					{
						case _RED:
						{
							break;
						}
	
						case _WORM:
						{
							break;
						}

						case _TOWER:
						{
							break;
						}
						case _TOWER2:
						{
							break;
						}

						case _ROBOT:
						{
							if (e->floor == false) 
							{
								frame = &e->anim.frames[3];
							}
	
							else if (e->floor == true && e->right == true) 
							{
								unsigned int frame_num = 6;
								if (frame_num != 8)
									frame_num++;

								if (frame_num == 8)
									frame_num = 6;

								frame = &e->anim.frames[frame_num];
							}

							else if (e->floor == true && e->right == false)
							{
								unsigned int frame_num = (10 - 10);
								if (frame_num != (12 - 10))
									frame_num++;

								if (frame_num == (12 - 10))
									frame_num = (10 - 10);

								frame = &e->anim.frames[frame_num];
							}

							break;
						}

					}
					break;
						
				}

				case eCurv:
				{
					if (e->position.y < 100)
						e->position.y++;

					else if (110 > e->position.y && e->position.y >= 100) {
						e->position.y++;
						e->position.x--;
					}
					else
						e->position.x--;

					switch (e->type)
					{
					case _RED:
					{
						break;
					}

					case _WORM:
					{
						

						if (e->position.y < 100)
							frame = &e->anim.frames[8];

						else if (110 > e->position.y && e->position.y >= 100)
						{
							unsigned int frame_num = (e->position.y - 100) / 10 ;
							frame = &e->anim.frames[7 - frame_num];
						}

						else
							frame = &e->anim.frames[4];

						break;
					}

					case _TOWER:
					{
						break;
					}
					case _TOWER2:
					{
						break;
					}

					case _ROBOT:
					{
						break;
					}

					}

					break;
				}

				case eT: 
				{
					switch (e->type)
					{
						case _RED:
						{
							break;
						}

						case _WORM:
						{
							break;
						}

						case _TOWER:
						{
							float sx, sy;
							sx = (App->player->position.x - e->position.x);
							sy = (App->player->position.y - e->position.y);

							if (sx < 0 && sy < 10){
								frame = &e->anim.frames[0];
							}
							else if (sx <= -10 && sy >= 10){
								frame = &e->anim.frames[1];
							}
							else if (sx > -10 && sx < 0 && sy >= 0){
								frame = &e->anim.frames[2];
							}
							//---------------------------------
							else if (sx < 10 && sx > 0 && sy >= 0){
								frame = &e->anim.frames[3];
							}
							else if (sx >= 10 && sy >= 10){
								frame = &e->anim.frames[4];
							}
							else if (sx > 0 && sy < 10){
								frame = &e->anim.frames[5];
							}
							




							break;
						}
						case _TOWER2:
						{
							float sx, sy;
							sx = (App->player->position.x - e->position.x);
							sy = (App->player->position.y - e->position.y);

							if (sx < 0 && sy > -10){
								frame = &e->anim.frames[0];
							}
							else if (sx <= -10 && sy <= -10){
								frame = &e->anim.frames[1];
							}
							else if (sx > -10 && sx < 0 && sy <= 0){
								frame = &e->anim.frames[2];
							}
							//---------------------------------
							else if (sx < 10 && sx > 0 && sy <= 0){
								frame = &e->anim.frames[3];
							}
							else if (sx >= 10 && sy <= -10){
								frame = &e->anim.frames[4];
							}
							else if (sx > 0 && sy > -10){
								frame = &e->anim.frames[5];
							}
							
							
							break;
						}

						case _ROBOT:
						{
							break;
						}

					}

					break;
				}
			}
		}
		
		if (tmp->data->alive)
		{
			e->collider->rect.x = e->position.x;
			e->collider->rect.y = e->position.y;

			App->renderer->Blit(graphics, e->position.x, e->position.y, frame);

			unsigned int a = rand() % 500 + 1;

			if (shooting == true && a == 1 && e->on_screen == true)
			{
				float sx, sy;
				
				sx = (App->player->position.x - e->position.x);
				sy = (App->player->position.y - e->position.y);

				App->particles->shot.speed.x = sx / sqrt(sx * sx + sy * sy) * 3.0f;
				App->particles->shot.speed.y = sy / sqrt(sx * sx + sy * sy) * 3.0f;
								
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
				if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT || c1->type == COLLIDER_PLAYER_SHOT_CHARGED || c2->type == COLLIDER_PLAYER_SHOT_CHARGED || c1->type == COLLIDER_PLAYER_SHOT_POWERUP || c2->type == COLLIDER_PLAYER_SHOT_POWERUP)
				{
					e->alive = false;
					e->collider->to_delete = true;
					App->particles->AddParticle(App->particles->enemy_death, e->position.x, e->position.y);
				}
				if (c1->type == COLLIDER_WALL || c2->type == COLLIDER_WALL)
				{
					if (e->floor == false)
					{
						e->position.y--;
						e->floor = true;
						e->right = false;
					}
					if (e->floor == true)
					{
						if (c1->rect.x < e->position.x || c2->rect.x < e->position.x)
							e->right = true;
						if (c1->rect.x > e->position.x || c2->rect.x > e->position.x)
							e->right = false;
						
					}

				}


			}
		}
		tmp = tmp->next;
	}


}

Enemy* ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y, eMov_Type mov, float fase)
{
	Enemy* e = new Enemy(enemy);
	e->position.x = x;
	e->position.y = y;
	e->fase = fase;
	e->initial_height = y;
	if (e->type == _RED || e->type == _WORM)
	e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 21, 24 }, COLLIDER_ENEMY, this);

	if (e->type == _ROBOT)
		e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 32, 32 }, COLLIDER_ENEMY, this);

	if (e->type == _TOWER || e->type == _TOWER2)
		e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 16, 16 }, COLLIDER_ENEMY, this);

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
