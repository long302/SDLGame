#include "GameSystem.h"

void GameSystem::Spawn::Player(const Vec2d<float>& pos,SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	 auto player=em.AddEntity(EntityType::PLAYER);
	 player->Add<Controller>()
		 ->Add<Transformer>()
		 ->Add<Renderer>()
		 ->Add<Physics>()
		 ->Add<Collider>()
		 ->Add<Imager>();
	 //transform
	 auto t = player->Get<Transformer>();
	 t->SetPos(pos);

	 //physic
	 auto player_p = player->Get<Physics>();
	 player_p->Add<Gravity>()
		 ->Add<Drag>()
		 ->Add<Movement>()
		 ->Add<Reaction>();
	 //collide
	 auto col = player->Get<Collider>()->GetHitBox().SetRect(t->GetPos().y, t->GetPos().x, 100, 100);
	 //image
	 TextureManager& tm = TextureManager::GetInstance();
	 auto img = player->Get<Imager>()->SetTexture(&tm.GetTexture(player->GetType(), TextureType::NONE));
	//render
	 auto r = player->Get<Renderer>();
	 r->SetRenderer(renderer);
}
void GameSystem::Spawn::NormalEnermy(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto enermy = em.AddEntity(EntityType::NORMAL_ENERMY);
	enermy->Add<AutoControl>()
		->Add<Transformer>()
		->Add<Renderer>()
		->Add<Physics>()
		->Add<Collider>()
		->Add<Imager>();
	auto t = enermy->Get<Transformer>();
	t->SetPos(pos);
	auto col = enermy->Get<Collider>()->GetHitBox().SetRect(t->GetPos().y, t->GetPos().x, 100, 100);
	auto p = enermy->Get<Physics>();
	p->Add<Gravity>()
		->Add<Drag>()
		->Add<Movement>()
		->Add<Reaction>();
	auto r = enermy->Get<Renderer>();
	r->SetRenderer(renderer);
	TextureManager& tm = TextureManager::GetInstance();


	enermy->Get<Imager>()->SetTexture(&tm.GetTexture(enermy->GetType(), TextureType::NONE));
}
void GameSystem::Spawn::Bullet(const Vec2d<float>& pos, SDL_Renderer* renderer, const Vec2d<float>& velocity)
{
	EntityManager& em = EntityManager::GetInstance();
	auto bullet = em.AddEntity(EntityType::BULLET);
	bullet->Add<Collider>()
		->Add<BulletTransformer>()
		->Add<Renderer>()
		->Add<Imager>()
		->Add<BulletController>();
	auto t = bullet->Get<BulletTransformer>();
	t->SetPos(pos);
	auto col = bullet->Get<Collider>()->GetHitBox().SetRect(t->GetPos().y, t->GetPos().x, 25, 25);
	auto r = bullet->Get<Renderer>();
	r->SetRenderer(renderer);
	bullet->Get<BulletController>()->SetSpeed(30.0)
		->SetVelocity(velocity);
	TextureManager& tm = TextureManager::GetInstance();
	bullet->Get<Imager>()->SetTexture(&tm.GetTexture(bullet->GetType(), TextureType::NONE));
}
void GameSystem::Spawn::Ground(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto ground = em.AddEntity(EntityType::GROUND);
	ground->Add<BulletTransformer>()
		->Add<Imager>()
		->Add<Collider>()
		->Add<Renderer>();
}
void GameSystem::Recall::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for(auto& player: em.GetEntity(EntityType::PLAYER))
	{
		auto player_t = player->Get<Transformer>();
		for (auto& bullets : em.GetEntity(EntityType::BULLET))
		{
			auto b_t = bullets->Get<BulletTransformer>();
			float distance = (player_t->GetPos() - b_t->GetPos()).Length();
			if (distance > 20000.0)
			{
				bullets->SetState(EntityState::DEAD);
			}
		}
	}
	for (auto& vec_e : em.GetAllEntity())
	{
		for (int i = 0; i < vec_e.second.size(); i++)
		{
			if (vec_e.second[i]->GetState() == EntityState::DEAD)
			{
				vec_e.second.erase(vec_e.second.begin() + i);
				i--;
			}		
		}
	}
}
void GameSystem::Control::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	int count = 0;
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto c = e->Get<Controller>();
		c->Update();	
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto c = e->Get<AutoControl>();
		c->Update();
	}
	for (auto& e : em.GetEntity(EntityType::BULLET))
	{
		auto c = e->Get<BulletController>();
		c->Update();
	}

}
void GameSystem::HandleControl::Update()
{
	AudioManager& am = AudioManager::GetInstance();
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto p = e->Get<Physics>();
		auto c = e->Get<Controller>();
		for (ControlState cs : c->GetState())
		{
			switch (cs)
			{
			case ControlState::NONE:
				break;
			case ControlState::ATTACK:
				break;
			case ControlState::JUMP:
				p->IncreaseForce({ 0.0,-5.0 });
				p->Get<Gravity>()->SetAcceleration(1.0);
				break;
			case ControlState::RUN_LEFT:
				p->Get<Movement>()->SetAcceleration(1.0f)
					->SetVelocity({ -1.0,0.0 });				
				break;
			case ControlState::RUN_RIGHT:
				p->Get<Movement>()->SetAcceleration(1.0f)
					->SetVelocity({ 1.0,0.0 });
				break;
			case ControlState::USING_SK1:
				auto col = e->Get<Collider>();
				auto t = e->Get<Transformer>();
				auto r = e->Get<Renderer>();
				auto p = e->Get<Physics>();
				Vec2d<float> vel = mouse.GetPos()+ g_pos - col->GetHitBox().GetRect().GetMidPos();
				vel.Normalize();
				p->IncreaseForce(vel * -1 );
				GameSystem::Spawn::Bullet(col->GetHitBox().GetRect().GetMidPos() + (vel * (col->GetHitBox().GetRect().w+ col->GetHitBox().GetRect().h) / 2.0),
					r->GetRenderer(),
					vel);
				am.PlayAudio(EntityType::PLAYER, AudioType::SHOOT);
				break;
			}
		}
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto p = e->Get<Physics>();
		auto c = e->Get<AutoControl>();
		for (ControlState cs : c->GetState())
		{
			switch (cs)
			{
			case ControlState::NONE:
				break;
			case ControlState::ATTACK:
				break;
			case ControlState::JUMP:
				p->IncreaseForce({ 0.0,-5.0 });
				p->Get<Gravity>()->SetAcceleration(1.0);
				break;
			case ControlState::RUN_LEFT:
				p->Get<Movement>()->SetAcceleration(1.0f)
					->SetVelocity({ -1.0,0.0 });
				p->Get<Drag>()->SetAcceleration(0.1);
				break;
			case ControlState::RUN_RIGHT:
				p->Get<Movement>()->SetAcceleration(1.0f)
					->SetVelocity({ 1.0,0.0 });
				p->Get<Drag>()->SetAcceleration(0.1);
				break;
			case ControlState::USING_SK1:
				break;
			}
		}
	}
}
void GameSystem::Physic::Update()
{
	AudioManager& am = AudioManager::GetInstance();
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto p = e->Get<Physics>();
		auto c = e->Get<Controller>();
		auto t = e->Get<Transformer>();
	
		if (t->GetOnGround())
		{
			if(p->GetForce().y>0.0) p->SetForce({ p->GetForce().x,0.0 });				
		}
		else
		{
			p->Get<Gravity>()->SetAcceleration(1.0);
			p->Get<Reaction>()->SetAcceleration(0.0)
				->SetVelocity({ 0.0,0.0 });
		}
		p->Update();
		
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto p = e->Get<Physics>();
		auto c = e->Get<AutoControl>();
		auto t = e->Get<Transformer>();
		
		
		if (t->GetOnGround())
		{
			if (p->GetForce().y > 0.0) p->SetForce({ p->GetForce().x,0.0 });

		}
		else
		{
			p->Get<Gravity>()->SetAcceleration(1.0);
			p->Get<Reaction>()->SetAcceleration(0.0)
				->SetVelocity({ 0.0,0.0 });
		}
		p->Update();
	}
	
}
void GameSystem::Transform::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto t = e->Get<Transformer>();
		auto p = e->Get<Physics>();
		t->Increase((p->GetVelocity()));
		t->Update();
		
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto t = e->Get<Transformer>();
		auto p = e->Get<Physics>();
		t->Increase((p->GetVelocity()));
		t->Update();
	}
	for (auto& e : em.GetEntity(EntityType::BULLET))
	{
		auto t = e->Get<BulletTransformer>();
		auto c = e->Get<BulletController>();
		t->Increase(c->GetVelocity()*c->GetSpeed());
		t->Update();
	}
}
void GameSystem::Collide::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	//player with normal enermy
	for (auto& player : em.GetEntity(EntityType::PLAYER))
	{
		auto player_col = player->Get<Collider>();
		auto player_t = player->Get<Transformer>();
		player_col->GetHitBox().SetRect(player_t->GetPos().y, player_t->GetPos().x, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		for (auto& normal_enermy : em.GetEntity(EntityType::NORMAL_ENERMY))
		{
			auto ne_col = normal_enermy->Get<Collider>();
			auto ne_t = normal_enermy->Get<Transformer>();
			ne_col->GetHitBox().SetRect(ne_t->GetPos().y, ne_t->GetPos().x, ne_col->GetHitBox().GetRect().w, ne_col->GetHitBox().GetRect().h);
			if(player_col->GetHitBox().CollideDetect(ne_col->GetHitBox()))
			{
				const Rectangle& rect=player_col->GetHitBox().GetOverlab(ne_col->GetHitBox());

				if (rect.GetMidPos().x < ne_col->GetHitBox().GetRect().GetMidPos().x)
				{
					ne_t->Increase({ rect.w/8.0f,0 });
				}
				else
				{
					ne_t->Decrease({ rect.w/8.0f,0 });
				}
			}
		}
		
	}
	//bullet with all
	for (auto& bullet : em.GetEntity(EntityType::BULLET))
	{
		auto& bullet_col = bullet->Get<Collider>();
		auto bullet_t = bullet->Get<BulletTransformer>();
		bullet_col->GetHitBox().SetRect(bullet_t->GetPos().y, bullet_t->GetPos().x, bullet_col->GetHitBox().GetRect().w, bullet_col->GetHitBox().GetRect().h);
		for (auto& normal_enermy : em.GetEntity(EntityType::NORMAL_ENERMY))
		{
			auto& normal_enermy_col = normal_enermy->Get<Collider>();
			if (bullet_col->GetHitBox().CollideDetect(normal_enermy_col->GetHitBox()))
			
			{
				bullet->SetState(EntityState::DEAD);

			}
		}
		for (auto& player : em.GetEntity(EntityType::PLAYER))
		{
			auto& player_col = player->Get<Collider>();
			if (bullet_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
			{
				bullet->SetState(EntityState::DEAD);

			}
		}
	}

}
void GameSystem::Assets::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	
}
void GameSystem::Render::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ pos.x - g_pos.x,pos.y - g_pos.y,rect.w,rect.h })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ pos.x - g_pos.x,pos.y - g_pos.y,rect.w,rect.h })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::BULLET))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<BulletTransformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ pos.x - g_pos.x,pos.y - g_pos.y,rect.w,rect.h })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();


	}
}

