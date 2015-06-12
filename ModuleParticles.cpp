#include <math.h>
#include "Globals.h"
#include "Application.h"

#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/particles.png");
	//enemy_explosion = App->textures->Load("ExplosionSprites.png");

	/*// Explosion particle
	explosion.fx = App->audio->LoadFx("rtype/explosion.wav");
	explosion.anim.frames.PushBack({274, 296, 33, 30});
	explosion.anim.frames.PushBack({313, 296, 33, 30});
	explosion.anim.frames.PushBack({346, 296, 33, 30});
	explosion.anim.frames.PushBack({382, 296, 33, 30});
	explosion.anim.frames.PushBack({419, 296, 33, 30});
	explosion.anim.frames.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;*/

	// Laser particle
	laser.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser.anim.frames.PushBack({ 249, 90, 13, 4 });
	laser.anim.loop = false;
	laser.speed.x = 7;
	laser.life = 1000;
	laser.anim.speed = 0.7f;

	// Laser anim
	//laser_anim.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_anim.anim.frames.PushBack({ 215, 85, 14, 12 });
	laser_anim.anim.frames.PushBack({ 233, 85, 14, 12 });
	laser_anim.anim.loop = false;
	laser_anim.anim.speed = 0.7f;

	//laser explosion
	laser_explosion.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_explosion.anim.frames.PushBack({ 287, 85, 14, 12 });
	laser_explosion.anim.frames.PushBack({ 300, 85, 14, 12 });
	laser_explosion.anim.loop = false;
	laser_explosion.anim.speed = 0.7f;

	// Laser charged
	laser_charged1.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged1.anim.frames.PushBack({ 232, 103, 16, 12 });
	laser_charged1.anim.frames.PushBack({ 249, 103, 14, 12 });
	laser_charged1.anim.loop = true;
	laser_charged1.speed.x = 7;
	laser_charged1.life = 1000;
	laser_charged1.lifes = 2;
	laser_charged1.anim.speed = 0.2f;

	// Laser charged
	laser_charged2.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged2.anim.frames.PushBack({ 200, 120, 32, 12 });
	laser_charged2.anim.frames.PushBack({ 233, 120, 32, 12 });
	laser_charged2.anim.loop = true;
	laser_charged2.speed.x = 7;
	laser_charged2.life = 1000;
	laser_charged2.lifes = 2;
	laser_charged2.anim.speed = 0.2f;

	// Laser charged
	laser_charged3.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged3.anim.frames.PushBack({ 168, 136, 48, 14 });
	laser_charged3.anim.frames.PushBack({ 217, 136, 48, 14 });
	laser_charged3.anim.loop = true;
	laser_charged3.speed.x = 7;
	laser_charged3.life = 1000;
	laser_charged3.lifes = 3;
	laser_charged3.anim.speed = 0.2f;

	// Laser charged
	laser_charged4.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged4.anim.frames.PushBack({ 136, 154, 64, 14 });
	laser_charged4.anim.frames.PushBack({ 201, 154, 64, 14 });
	laser_charged4.anim.loop = true;
	laser_charged4.speed.x = 7;
	laser_charged4.life = 1000;
	laser_charged4.lifes = 4;
	laser_charged4.anim.speed = 0.2f;

	// Laser charged
	laser_charged5.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged5.anim.frames.PushBack({ 104, 170, 80, 16 });
	laser_charged5.anim.frames.PushBack({ 185, 170, 80, 16 });
	laser_charged5.anim.loop = true;
	laser_charged5.speed.x = 7;
	laser_charged5.life = 1000;
	laser_charged5.lifes = 5;
	laser_charged5.anim.speed = 0.2f;

	// Laser charged anim
	//laser_charged_anim.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged_anim.anim.frames.PushBack({ 1, 51, 32, 32 });
	laser_charged_anim.anim.frames.PushBack({ 34, 51, 29, 32 });
	laser_charged_anim.anim.frames.PushBack({ 67, 51, 30, 32 });
	laser_charged_anim.anim.frames.PushBack({ 102, 51, 27, 32 });
	laser_charged_anim.anim.frames.PushBack({ 134, 51, 30, 32 });
	laser_charged_anim.anim.frames.PushBack({ 167, 51, 27, 32 });
	laser_charged_anim.anim.frames.PushBack({ 199, 51, 24, 32 });
	laser_charged_anim.anim.frames.PushBack({ 232, 51, 21, 32 });
	laser_charged_anim.anim.loop = true;
	laser_charged_anim.life = 9999999999;
	laser_charged_anim.anim.speed = 0.1f;
	laser_charged_anim.follow_player = true;

	// Laser explosion charged
	//laser_charged_explosion.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser_charged_explosion.anim.frames.PushBack({ 0, 191, 56, 48 });
	laser_charged_explosion.anim.frames.PushBack({ 56, 191, 56, 48 });
	laser_charged_explosion.anim.frames.PushBack({ 112, 191, 56, 48 });
	laser_charged_explosion.anim.frames.PushBack({ 168, 191, 56, 48 });
	laser_charged_explosion.anim.frames.PushBack({ 224, 191, 56, 48 });
	laser_charged_explosion.anim.loop = false;
	laser_charged_explosion.anim.speed = 0.2f;

	//Laser powerup
	laser_powerup.anim.frames.PushBack({ 31, 829, 12, 36 });
	laser_powerup.anim.frames.PushBack({ 48, 824, 18, 46 });
	laser_powerup.anim.frames.PushBack({ 81, 820, 27, 54 });
	laser_powerup.anim.frames.PushBack({ 114, 819, 37, 56 });
	laser_powerup.anim.frames.PushBack({ 163, 819, 47, 56 });
	laser_powerup.anim.frames.PushBack({ 212, 819, 47, 56 });
	laser_powerup.anim.frames.PushBack({ 17, 885, 61, 56 });
	laser_powerup.anim.frames.PushBack({ 82, 885, 64, 56 });
	laser_powerup.anim.frames.PushBack({ 149, 885, 60, 56 });
	laser_powerup.anim.frames.PushBack({ 212, 885, 64, 56 });

	laser_powerup.anim.frames.PushBack({ 147, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 217, 1077, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 152, 1110, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 212, 1110, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 343, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 22, 1077, 59, 32 });
	laser_powerup.anim.frames.PushBack({ 147, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 217, 1077, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 152, 1110, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 212, 1110, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 343, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 22, 1077, 59, 32 });
	laser_powerup.anim.frames.PushBack({ 147, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 217, 1077, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 152, 1110, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 212, 1110, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 343, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 22, 1077, 59, 32 });
	laser_powerup.anim.frames.PushBack({ 147, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 217, 1077, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 152, 1110, 58, 32 });
	laser_powerup.anim.frames.PushBack({ 212, 1110, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 343, 1077, 64, 32 });
	laser_powerup.anim.frames.PushBack({ 22, 1077, 59, 32 });

	laser_powerup.anim.loop = false;
	laser_powerup.anim.speed = 0.5f;
	laser_powerup.speed.x = 5;
	laser_powerup_anim.speed.x = 5;

	/*//Laser powerup_anim
	laser_powerup_anim.anim.frames.PushBack({ 147, 1077, 64, 32 });
	laser_powerup_anim.anim.frames.PushBack({ 217, 1077, 58, 32 });
	laser_powerup_anim.anim.frames.PushBack({ 152, 1110, 58, 32 });
	laser_powerup_anim.anim.frames.PushBack({ 212, 1110, 64, 32 });
	laser_powerup_anim.anim.frames.PushBack({ 343, 1077, 64, 32 });
	laser_powerup_anim.anim.frames.PushBack({ 22, 1077, 59, 32 });
	laser_powerup_anim.anim.loop = true;
	laser_powerup_anim.anim.speed = 0.3f;
	laser_powerup_anim.speed.x = 5;
	laser_powerup_anim.life = 1000;*/

	//Explosion_Player
	explosion.anim.frames.PushBack({ 1, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 35, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 69, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 103, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 137, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 169, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 201, 343, 32, 28 });
	explosion.anim.frames.PushBack({ 233, 343, 34, 28 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	//Enemy explosion
	enemy_death.anim.frames.PushBack({ 128, 384, 31, 31 });
	enemy_death.anim.frames.PushBack({ 161, 384, 31, 31 });
	enemy_death.anim.frames.PushBack({ 192, 384, 31, 31 });
	enemy_death.anim.frames.PushBack({ 226, 384, 31, 31 });
	enemy_death.anim.frames.PushBack({ 260, 384, 31, 31 });
	enemy_death.anim.frames.PushBack({ 292, 384, 31, 31 });
	enemy_death.anim.loop = false;
	enemy_death.anim.speed = 0.2f;

	//EnemyShot
	shot.anim.frames.PushBack({ 212, 279, 6, 6 });
	shot.anim.loop = false;
	shot.anim.speed = 0.0f;
	shot.life = 8000;

	//Power up
	power_up.anim.frames.PushBack({ 0, 560, 14, 14 });
	power_up.anim.loop = false;
	power_up.anim.speed = 0.0f;

	//Laser blue
	laser_blue.anim.frames.PushBack({ 122, 640, 16, 3 }); //Pla
	laser_blue.anim.loop = false;
	laser_blue.anim.speed = 0.0f;
	laser_blue.speed.x = 7;
	laser_blue.life = 10000;

	//Laser blue2
	laser_blue2.anim.frames.PushBack({ 168, 599, 16, 18 });//Diagonal baix esquerra
	laser_blue2.anim.frames.PushBack({ 147, 632, 8, 18 });//Separació
	laser_blue2.anim.frames.PushBack({ 168, 665, 16, 18 });//Diagonal baix dreta
	laser_blue2.anim.frames.PushBack({ 160, 657, 32, 34 });//Diagonal baix dreta
	laser_blue2.anim.frames.PushBack({ 160, 591, 32, 34 });//Diagonal baix esquerra
	laser_blue2.anim.frames.PushBack({ 185, 575, 16, 9 });//Rebot superior
	laser_blue2.anim.frames.PushBack({ 185, 698, 16, 9 });//Rebot inferior
	laser_blue2.anim.frames.PushBack({ 226, 632, 8, 18 });//Rebot dreta
	laser_blue2.anim.loop = false;
	laser_blue2.anim.speed = 0.0f;
	laser_blue2.speed.x = 7;
	laser_blue2.speed.y = -7;
	laser_blue2.life = 10000;

	//Laser blue3
	laser_blue3.anim.frames.PushBack({ 168, 665, 16, 18 });//Diagonal baix dreta
	laser_blue3.anim.frames.PushBack({ 147, 632, 8, 18 });//Separacio
	laser_blue3.anim.frames.PushBack({ 168, 599, 16, 18 });//Diagonal baix esquerra
	laser_blue3.anim.frames.PushBack({ 147, 632, 8, 18 });//Separació
	laser_blue3.anim.frames.PushBack({ 160, 657, 32, 34 });//Diagonal baix dreta
	laser_blue3.anim.frames.PushBack({ 160, 591, 32, 34 });//Diagonal baix esquerra
	laser_blue3.anim.frames.PushBack({ 185, 575, 16, 9 });//Rebot superior
	laser_blue3.anim.frames.PushBack({ 185, 698, 16, 9 });//Rebot inferior
	laser_blue3.anim.frames.PushBack({ 226, 632, 8, 18 });//Rebot dreta
	laser_blue3.anim.loop = false;
	laser_blue3.anim.speed = 0.0f;
	laser_blue3.speed.x = 7;
	laser_blue3.speed.y = 7;
	laser_blue3.life = 10000;


	boss_ex.anim.frames.PushBack({ 64, 415, 64, 64 });
	boss_ex.anim.frames.PushBack({ 129, 415, 64, 64 });
	boss_ex.anim.frames.PushBack({ 195, 415, 64, 64 });
	boss_ex.anim.frames.PushBack({ 260, 415, 64, 64 });
	boss_ex.anim.frames.PushBack({ 0, 481, 64, 64 });
	boss_ex.anim.frames.PushBack({ 64, 481, 64, 64 });
	boss_ex.anim.frames.PushBack({ 129, 481, 64, 64 });
	boss_ex.anim.frames.PushBack({ 194, 481, 64, 64 });
	boss_ex.anim.frames.PushBack({ 259, 481, 64, 64 });
	boss_ex.anim.loop = false;
	boss_ex.anim.speed = 0.2f;

	//numbers
	numbers.anim.frames.PushBack({ 595, 1376, 70, 71 });
	numbers.anim.frames.PushBack({ 2, 1376, 65, 71 });
	numbers.anim.frames.PushBack({ 69, 1376, 65, 71 });
	numbers.anim.frames.PushBack({ 134, 1376, 65, 71 });
	numbers.anim.frames.PushBack({ 203, 1376, 65, 71 });
	numbers.anim.frames.PushBack({ 270, 1376, 65, 71 });
	numbers.anim.frames.PushBack({ 334, 1376, 65, 71 });
	numbers.anim.frames.PushBack({ 400, 1376, 70, 71 });
	numbers.anim.frames.PushBack({ 466, 1376, 70, 71 });
	numbers.anim.frames.PushBack({ 527, 1376, 70, 71 });
	numbers.anim.frames.PushBack({ 597, 1376, 70, 71 });
	numbers.anim.frames.PushBack({ 597, 1376, 70, 71 });
	numbers.anim.loop = false;
	numbers.anim.speed = 0.015f;

	number10.anim.frames.PushBack({ 550, 1376, 121, 71 });
	number10.anim.loop = false;
	number10.anim.speed = 0.015f;

	//UI
	// lifes
	lifes.anim.frames.PushBack({ 31, 560, 13, 14 });
	lifes.anim.loop = false;
	lifes.speed.x = 0;
	lifes.follow_window = true;
	lifes.anim.speed = 0.0f;

	// beam
	beam.anim.frames.PushBack({ 485, 557, 384, 16 });
	beam.anim.loop = false;
	beam.speed.x = 0;
	beam.follow_window = true;
	beam.anim.speed = 0.0f;

	// bar
	bar.anim.frames.PushBack({ 405, 585, 201, 8 });
	bar.anim.loop = false;
	bar.speed.x = 0;
	bar.anim.speed = 0.0f;
	bar.bar = true;

	//Boss boss_sh.anim
	boss_sh.anim.frames.PushBack({ 576, 2064, 22, 19 });
	boss_sh.anim.frames.PushBack({ 601, 2064, 22, 19 });
	boss_sh.anim.frames.PushBack({ 626, 2064, 22, 19 });
	boss_sh.anim.frames.PushBack({ 652, 2064, 22, 19 });
	boss_sh.anim.loop = false;
	boss_sh.anim.speed = 0.1f;

	bar_move = 0;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	active.clear();

	return true;
}

bool ModuleParticles::CleanUpActiveParticles()
{
	active.clear();

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Particle* p = tmp->data;
		tmp_next = tmp->next;

		if (p->Update() == false)
		{
			delete p;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= p->born)
		{
			if (p == &laser_blue2 || p == &laser_blue3) {

				if (laser_blue2.speed.x > 0 && laser_blue2.speed.y < 0 || laser_blue3.speed.x > 0 && laser_blue3.speed.y < 0){
					if (p->bounceT == false && p->bounceR == false)
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[0]);
					if (p->bounceT == true) {
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[3]);
						laser_blue2.speed.y *= -1;
					}
					else if (p->bounceR == true){
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[5]);
						laser_blue2.speed.x *= -1;
					}
				}
				if (laser_blue2.speed.x > 0 && laser_blue2.speed.y > 0 || laser_blue3.speed.x > 0 && laser_blue3.speed.y > 0){
					if (p->bounceB == false && p->bounceR == false)
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[0]);
					if (p->bounceB == true) {
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[4]);
						laser_blue2.speed.y *= -1;
					}
					else if (p->bounceR == true){
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[5]);
						laser_blue2.speed.x *= -1;
					}
				}

				if (laser_blue2.speed.x < 0 && laser_blue2.speed.y > 0 || laser_blue3.speed.x < 0 && laser_blue3.speed.y > 0){
					if (p->bounceB == false && p->bounceL == false)
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[0]);
					if (p->bounceB == true) {
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[4]);
						laser_blue2.speed.y *= -1;
					}
					else if (p->bounceL == true){
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[1]);
						laser_blue2.speed.x *= -1;
					}
				}
				if (laser_blue2.speed.x < 0 && laser_blue2.speed.y < 0 || laser_blue3.speed.x < 0 && laser_blue3.speed.y < 0){
					if (p->bounceT == false && p->bounceL == false)
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[0]);
					if (p->bounceT == true) {
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[3]);
						laser_blue2.speed.y *= -1;
					}
					else if (p->bounceL == true){
						App->renderer->Blit(graphics, p->position.x, p->position.y, &p->anim.frames[1]);
						laser_blue2.speed.x *= -1;
					}
				}

			}
			else
				App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		if (p->follow_player == true)
		{
			p->position.x = App->player->position.x + 32;
			p->position.y = App->player->position.y - 9;
			if (App->player->charging == false)
			{
				delete p;
				active.del(tmp);
			}
		}

		if (p->follow_window == true)
		{
			p->position.x = p->initial_position.x + App->renderer->camera.x / -3;
		}

		if (p->bar == true)
		{
			
			if (App->player->charging == true)
			{
				p->position.x = p->initial_position.x + App->renderer->camera.x / -3 - bar_move;

				if ((SDL_GetTicks() - App->player->charge) / 5 < 200)
				{
					bar_move = ((SDL_GetTicks() - App->player->charge) / 5);
				}
				else if ((SDL_GetTicks() - App->player->charge) / 5 > 200)
					bar_move = 201;

				p->position.x = p->initial_position.x + App->renderer->camera.x / -3 + bar_move;
			}
			else if (bar_move != 0)
			{
				p->position.x = p->initial_position.x + App->renderer->camera.x / -3 - bar_move;
				bar_move = 0;
			}
			else
				p->position.x = p->initial_position.x + App->renderer->camera.x / -3;
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Particle*>* tmp = active.getFirst();

	while (tmp != NULL)
	{
		if (tmp->data->collider == c1)
		{
			if (c1->type == COLLIDER_PLAYER_SHOT)
			{
				if (c2->type == COLLIDER_WALL)
				{
					App->particles->AddParticle(App->particles->laser_explosion, c2->rect.x - 14, c1->rect.y - 5);
				}
				delete tmp->data;
				active.del(tmp);
				break;
			}

			else if (c1->type == COLLIDER_PLAYER_SHOT2 || c1->type == COLLIDER_WALL){

				if (c2->type == COLLIDER_WALL || c2->type == COLLIDER_WALL){
					if (c2->rect.x < c1->rect.x || c1->rect.x < c2->rect.x)
						tmp->data->bounceL = true;
					if (c2->rect.x > c1->rect.x || c1->rect.x > c2->rect.x)
						tmp->data->bounceR = true;
					if (c2->rect.y < c1->rect.y || c1->rect.y < c2->rect.y)
						tmp->data->bounceT = true;
					if (c2->rect.y > c1->rect.y || c1->rect.y > c2->rect.y)
						tmp->data->bounceB = true;
				}
					

			}

			else if (c1->type == COLLIDER_PLAYER_SHOT_CHARGED)
			{
				if (c2->type == COLLIDER_WALL && c2->rect.y > (c1->rect.y + (c1->rect.h / 2) + 2) || (c1->rect.y + (c1->rect.h / 2) - 2) > c2->rect.y + c2->rect.h)
				{
					
				}
				else if (c2->type == COLLIDER_WALL)
				{
					App->particles->AddParticle(App->particles->laser_charged_explosion, c2->rect.x - 28, c1->rect.y + c1->rect.h / 2 - 24);
					delete tmp->data;
					active.del(tmp);
					break;
				}

				else if (c2->type == COLLIDER_ENEMY)
				{
					tmp->data->lifes--;
					if (tmp->data->lifes == 0)
					{
						App->particles->AddParticle(App->particles->laser_charged_explosion, c2->rect.x - 28, c1->rect.y + c1->rect.h / 2 - 24);
						delete tmp->data;
						active.del(tmp);
						break;
					}
				}
			}

			else if (c1->type == COLLIDER_PLAYER_SHOT_POWERUP)
			{
				if (c2->type == COLLIDER_WALL && c2->rect.y > c1->rect.y + 22 || c1->rect.y + 10 > c2->rect.y + c2->rect.h)
				{
					
				}
				else if (c2->type == COLLIDER_WALL)
				{
					delete tmp->data;
					active.del(tmp);
					break;
				}
			}

			else
			{
				delete tmp->data;
				active.del(tmp);
				break;
			}
		}

		tmp = tmp->next;
	}
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	p->initial_position = p->position;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	active.add(p);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), follow_player(false), follow_window(false), bar(false), lifes(0), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
	follow_player = p.follow_player;
	follow_window = p.follow_window;
	lifes = p.lifes;
	bar = p.bar;
	initial_position = position;
}

Particle::~Particle()
{
	if (collider)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}