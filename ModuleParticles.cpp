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
	laser_anim.anim.frames.PushBack({ 215, 85, 14, 12 });
	laser_anim.anim.frames.PushBack({ 233, 85, 14, 12 });
	laser_anim.anim.loop = true;
	laser_anim.anim.speed = 0.7f;

	//laser explosion
	laser_explosion.anim.frames.PushBack({ 287, 85, 14, 12 });
	laser_explosion.anim.frames.PushBack({ 300, 85, 14, 12 });
	laser_explosion.anim.loop = false;
	laser_explosion.anim.speed = 0.7f;

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
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
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
			if (App->player->power_up == 0)
			{
				if (c1->type == COLLIDER_PLAYER_SHOT && c2->type == COLLIDER_WALL)
				{
					App->particles->AddParticle(App->particles->laser_explosion, c1->rect.x - 5, c1->rect.y - 5);
				}
				delete tmp->data;
				active.del(tmp);
				break;
			}
			else if (App->player->power_up == 1)
			{
				if (c1->type == COLLIDER_PLAYER_SHOT)
				{
					if (c2->type == COLLIDER_WALL && (c1->rect.y + 10 < c2->rect.y && c2->rect.y < c1->rect.y + 22 || c1->rect.y +10 < c2->rect.y + c2->rect.h && c2->rect.y + c2->rect.h < c1->rect.y + 22))
					{
						delete tmp->data;
						active.del(tmp);
						break;
					}
					else
					{


					}
				}

				else
				{
					delete tmp->data;
					active.del(tmp);
					break;
				}
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

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	active.add(p);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
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