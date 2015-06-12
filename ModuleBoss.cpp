#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"
#include <math.h>
#include <ctime>
#include <stdio.h>

ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleBoss::~ModuleBoss()
{}

bool ModuleBoss::Start()
{
	ship_is_here = false;
	can_shoot = false;

	position.x = 3930 - 93;
	position.y = 125;

	num_hits = 3;

	LOG("Loading Boss");
	graphics = App->textures->Load("rtype/Boss.png");

	body.frames.PushBack({ 27, 2, 155, 205 });
	body.frames.PushBack({ 189, 2, 155, 205 });
	body.frames.PushBack({ 351, 2, 155, 205 });
	body.frames.PushBack({ 189, 2, 155, 205 });
	body.loop = true;
	body.speed = 0.015f;
	alive = true;

	for (int j = 0; j < 194; j++)
	{
		eye[0].frames.PushBack({ 177 + j, 1927, 194 - j, 33 });
	}
	eye[0].loop = false;
	eye[0].speed = 1.0f;
	
	for (int j = 0; j < 105; j++)
	{
		eye[1].frames.PushBack({ 265 + j, 1982, 105 - j, 57 });
	}
	eye[1].loop = false;
	eye[1].speed = 1.0f;

	for (int j = 0; j < 192; j++)
	{
		eye[2].frames.PushBack({ 177 + j, 2054, 192 - j, 80 });
	}
	eye[2].loop = false;
	eye[2].speed = 1.0f;

	baby.frames.PushBack({ 636, 1928, 32, 32 });
	baby.frames.PushBack({ 603, 1928, 32, 32 });
	baby.frames.PushBack({ 570, 1928, 32, 32 });
	baby.frames.PushBack({ 537, 1928, 32, 32 });
	baby.frames.PushBack({ 504, 1928, 32, 32 });
	baby.frames.PushBack({ 471, 1928, 32, 32 });
	baby.frames.PushBack({ 636, 1964, 32, 32 });
	baby.frames.PushBack({ 603, 1964, 32, 32 });
	baby.frames.PushBack({ 570, 1964, 32, 32 });//
	baby.frames.PushBack({ 603, 1964, 32, 32 });
	baby.frames.PushBack({ 636, 1964, 32, 32 });
	baby.loop = false;
	baby.speed = 0.1f;

	baby_shot_before.frames.PushBack({ 636, 1964, 32, 32 });
	baby_shot_before.frames.PushBack({ 603, 1964, 32, 32 });
	baby_shot_before.frames.PushBack({ 570, 1964, 32, 32 });//
	baby_shot_before.loop = false;
	baby_shot_before.speed = 0.1f;

	baby_shot_after.frames.PushBack({ 570, 1964, 32, 32 });//
	baby_shot_after.frames.PushBack({ 603, 1964, 32, 32 });
	baby_shot_after.frames.PushBack({ 636, 1964, 32, 32 });
	baby_shot_after.loop = false;
	baby_shot_after.speed = 0.1f;


	collider_skin_head = App->collision->AddCollider({ 3930-165, 17, 105, 84 }, COLLIDER_WALL, this);
	collider_skin_neck = App->collision->AddCollider({ 3930 - 81, 102, 21, 11}, COLLIDER_WALL, this);
	collider_baby = App->collision->AddCollider({ 3930 - 93, 111, 32, 32 }, COLLIDER_ENEMY, this);
	collider_skin_bottom = App->collision->AddCollider({ 3930 - 76, 147, 16, 80 }, COLLIDER_WALL, this);

	tail = new BossTail(App, graphics);

	return true;
}

bool ModuleBoss::CleanUp()
{
	LOG("Unloading Boss");
	//delete[] tail;
	App->textures->Unload(graphics);

	return true;
}

update_status ModuleBoss::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleBoss::Update()
{
	
	//Moure cares
	if (alive)
	{
		App->renderer->Blit(graphics, 3930 - 165, 17, &body.GetCurrentFrame());

		if (ship_is_here)
		{
			App->renderer->Blit(graphics, 3930 - 93, 111, &baby.GetCurrentFrame());

			if (baby.IsOver())
			{
				can_shoot = true;
				Shooting();
			}

		}


		SDL_Rect frame;

		switch (num_hits)
		{
		case 3:
			App->renderer->Blit(graphics, 3930 - 198, 17, &eye[0].frames[0]);
			App->renderer->Blit(graphics, 3930 - 109, 70, &eye[1].frames[0]);
			App->renderer->Blit(graphics, 3930 - 198, 141, &eye[2].frames[0]);
			break;

		case 2:
			frame = eye[0].GetCurrentFrame();
			App->renderer->Blit(graphics, 3930 - 198 + 193 - frame.w, 17, &frame);
			App->renderer->Blit(graphics, 3930 - 109, 70, &eye[1].frames[0]);
			App->renderer->Blit(graphics, 3930 - 198, 141, &eye[2].frames[0]);
			break;

		case 1:
			frame = eye[1].GetCurrentFrame();
			App->renderer->Blit(graphics, 3930 - 109 + 104 - frame.w, 70, &eye[1].GetCurrentFrame());
			App->renderer->Blit(graphics, 3930 - 198, 141, &eye[2].frames[0]);
			break;

		case 0:
			frame = eye[2].GetCurrentFrame();
			App->renderer->Blit(graphics, 3930 - 198 + 191 - frame.w, 141, &eye[2].GetCurrentFrame());

			/*if (eye[2].IsOver())
			{*/

			App->particles->AddParticle(App->particles->boss_ex, 3830, 25);
			App->particles->AddParticle(App->particles->boss_ex, 3900, 75);
			App->particles->AddParticle(App->particles->boss_ex, 3850, 100);
			App->particles->AddParticle(App->particles->boss_ex, 3870, 125);
			App->particles->AddParticle(App->particles->boss_ex, 3890, 150);
			App->particles->AddParticle(App->particles->enemy_death, 3840, 30);
			App->particles->AddParticle(App->particles->enemy_death, 3840, 90);
			App->particles->AddParticle(App->particles->enemy_death, 3840, 150);

			Die();

			break;
			//}
			
		}
		return tail->Update();
	}
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
//colliders boss
	if (c1->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY)
	{
		if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
		{
			num_hits--;
		}
	}
	tail->OnCollision(c1, c2);
}

void ModuleBoss::Arrival()
{
	ship_is_here = true;
}

void ModuleBoss::Shooting()
{
	if (ship_is_here == true && can_shoot == true)
	{
		App->renderer->Blit(graphics, 3930 - 93, 111, &baby_shot_before.GetCurrentFrame());

		if (baby_shot_before.IsOver())
		{
			float sx, sy;
			
			App->particles->AddParticle(App->particles->boss_sh, position.x, position.y, COLLIDER_ENEMY_SHOT);
			
			sx = (App->player->position.x - position.x);
			sy = (App->player->position.y - position.y);
			
			App->particles->boss_sh.speed.x = sx / sqrt(sx * sx + sy * sy) * 3.0f;
			App->particles->boss_sh.speed.y = sy / sqrt(sx * sx + sy * sy) * 3.0f;

			can_shoot = true;
			
			App->renderer->Blit(graphics, 3930 - 93, 111, &baby_shot_after.GetCurrentFrame());
		}

		
	}
}
/**/
//tail

void ModuleBoss::Die()
{
	collider_skin_head->to_delete = true;
	collider_skin_neck->to_delete = true;
	collider_skin_bottom->to_delete = true;
	collider_baby->to_delete = true;

	alive = false;
}

BossTail::BossTail(Application* app, SDL_Texture* texture) : App(app), graphics (texture)
{
	//animacio final de la cua
	end.frames.PushBack({ 508, 2045, 16, 16 }); 
	end.frames.PushBack({ 526, 2045, 16, 16 });
	end.frames.PushBack({ 544, 2045, 16, 16 });
	end.frames.PushBack({ 562, 2045, 16, 16 });
	end.frames.PushBack({ 580, 2045, 16, 16 });
	end.frames.PushBack({ 598, 2045, 16, 16 });
	end.frames.PushBack({ 616, 2045, 16, 16 });
	end.frames.PushBack({ 634, 2045, 16, 16 });
	end.frames.PushBack({ 652, 2045, 16, 16 });
	end.frames.PushBack({ 634, 2045, 16, 16 });
	end.frames.PushBack({ 616, 2045, 16, 16 });
	end.frames.PushBack({ 598, 2045, 16, 16 });
	end.frames.PushBack({ 580, 2045, 16, 16 });
	end.frames.PushBack({ 562, 2045, 16, 16 });
	end.frames.PushBack({ 544, 2045, 16, 16 });
	end.frames.PushBack({ 526, 2045, 16, 16 });
	end.loop = true;
	end.speed = 0.15f;

	//grans
	piece_frame[0] = { 544, 2000, 16, 16 };
	piece_frame[1] = { 544, 2000, 16, 16 };
	piece_frame[2] = { 544, 2000, 16, 16 };
	piece_frame[3] = { 544, 2000, 16, 16 };
	piece_frame[4] = { 544, 2000, 16, 16 };
	piece_frame[5] = { 544, 2000, 16, 16 };
	piece_frame[6] = { 544, 2000, 16, 16 };
	//mitjanes
	piece_frame[7] = { 574, 2017, 14, 13 };
	piece_frame[8] = { 574, 2017, 14, 13 };
	piece_frame[9] = { 574, 2017, 14, 13 };
	piece_frame[10] = { 574, 2017, 14, 13 };
	piece_frame[11] = { 574, 2017, 14, 13 };
	piece_frame[12] = { 574, 2017, 14, 13 };
	//petites
	piece_frame[13] = { 600, 2032, 12, 11 };
	piece_frame[14] = { 600, 2032, 12, 11 };
	piece_frame[15] = { 600, 2032, 12, 11 };
	piece_frame[16] = { 600, 2032, 12, 11 };
	piece_frame[17] = { 600, 2032, 12, 11 };

	int pas = 6;
	int pos_y = SCREEN_HEIGHT - 53;
	int delta_y = 10;
	int pos_x =  3930 - 120;
	int delta_x = 16;

	for (int i = 0; i < 18; i++)
	{
		if (i == 7)
		{
			delta_x = 14;
			delta_y = 7;
			pos_x += 2;
			pos_y += 2;
			pas = 5;
		}

		if (i == 13)
		{
			delta_x = 12;
			delta_y = 5;
			pos_x += 1;
			pos_y += 1;
			pas = 4;
		}

		position[i].x = pos_x;
		position[i].y = pos_y;
		
		pos_x -= delta_x - pas;
		pos_y -= delta_y - pas;

		piece_collider[i] = App->collision->AddCollider({ position[i].x, position[i].y, delta_x, delta_y }, COLLIDER_WALL, App->boss);
	}

	position[18].x = pos_x - 4;
	position[18].y = pos_y - 5;

	piece_collider[18] = App->collision->AddCollider({ position[18].x, position[18].y, 16, 16 }, COLLIDER_WALL, App->boss);
}

BossTail::~BossTail()
{}


update_status BossTail::Update()
{
	for (int i = 0; i < 19; i++)
	{
		//moure cua
		if (App->boss->alive)
		{
			//actualitzar collider
			piece_collider[i]->rect.x = position[i].x;
			piece_collider[i]->rect.y = position[i].y;

			//pintar cua
			if (i == 18)
			{
				App->renderer->Blit(graphics, position[i].x, position[i].y, &end.GetCurrentFrame());
			}

			else
			{
				App->renderer->Blit(graphics, position[i].x, position[i].y, &piece_frame[i]);
			}
		}

		else
		{
			for (int i = 19; i >= 0; i--)
			{
				piece_collider[i]->to_delete = true;
			}
		}
	}
	return UPDATE_CONTINUE;
}

void BossTail::OnCollision(Collider* c1, Collider* c2)
{
	for (int i = 0; i < 19; i++)
	{
		if (c1 == piece_collider [i] || c2 == piece_collider [i])
		{
			if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
			{
				App->particles->OnCollision(c1, c2);
			}
			else
			{
				App->player->OnCollision(c1, c2);
			}
			break;
		}
	}
}

