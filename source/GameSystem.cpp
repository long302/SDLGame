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
		 ->Add<Equipments>()
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
	 player_p->SetMaxF({10.0,20.0});
	 //collide
	 player->Get<Collider>()->GetHitBox().SetRect(t->GetPos().y, t->GetPos().x, 100, 100);
	 //image
	 TextureManager& tm = TextureManager::GetInstance();
	 player->Get<Imager>()->SetTexture(&tm.GetTexture(player->GetType(), TextureType::NONE));
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
	p->SetMaxF({ 10.0,20.0 });
	//collide
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
		->Add<Transformer>()
		->Add<Renderer>()
		->Add<Imager>()
		->Add<Physics>()
		->Add<BulletController>();

	auto t = bullet->Get<Transformer>();
	t->SetPos(pos);
	auto col = bullet->Get<Collider>()->GetHitBox().SetRect(t->GetPos().y, t->GetPos().x, 25, 25);
	auto r = bullet->Get<Renderer>();
	r->SetRenderer(renderer);
	bullet->Get<BulletController>()->SetVelocity(velocity);
	auto p = bullet->Get<Physics>();
	auto c = bullet->Get<BulletController>();
	p->IncreaseForce(c->GetVelocity() * 30);
	p->Add<Gravity>();
	p->Get<Gravity>()->SetAcceleration(0.3);
	TextureManager& tm = TextureManager::GetInstance();
	bullet->Get<Imager>()->SetTexture(&tm.GetTexture(bullet->GetType(), TextureType::NONE));
}
void GameSystem::Spawn::Ground(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto ground = em.AddEntity(EntityType::GROUND);
	ground->Add<Transformer>()
		->Add<Imager>()
		->Add<Collider>()
		->Add<Renderer>();
	auto t = ground->Get<Transformer>();
	t->SetPos(pos);
	auto img = ground->Get<Imager>();
	TextureManager& tm = TextureManager::GetInstance();
	img->SetTexture(&tm.GetTexture(ground->GetType(),TextureType::NONE));
	auto col = ground->Get<Collider>();
	col->GetHitBox().SetRect(0, 0, 400, 100);
	auto r = ground->Get<Renderer>();
	r->SetRenderer(renderer);
}
void GameSystem::Spawn::BackGround(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto ground = em.AddEntity(EntityType::BACK_GROUND);
	ground->Add<Transformer>()
		->Add<Imager>()
		->Add<Collider>()
		->Add<Renderer>();
	auto t = ground->Get<Transformer>();
	t->SetPos(pos);
	auto img = ground->Get<Imager>();
	TextureManager& tm = TextureManager::GetInstance();
	img->SetTexture(&tm.GetTexture(ground->GetType(), TextureType::NONE));
	auto col = ground->Get<Collider>();
	col->GetHitBox().SetRect(0, 0, WIDTH*12.0f, HEIGHT*8.0f);
	auto r = ground->Get<Renderer>();
	r->SetRenderer(renderer);
}

void GameSystem::Spawn::DeadEffect(EntityType type, const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto& de=em.AddEntity(EntityType::DEAD_EFFECT);
	de->Add<Transformer>()
		->Add<Collider>()
		->Add<Imager>()
		->Add<Renderer>();

	auto de_t = de->Get<Transformer>();
	de_t->SetPos(pos);
	auto de_col = de->Get<Collider>();
	de_col->GetHitBox().SetRect(de_t->GetPos().x, de_t->GetPos().y, 100, 100);
	TextureManager& tm = TextureManager::GetInstance();

	de->Get<Imager>()->SetTexture(&tm.GetTexture(type, TextureType::DEAD));
	de->Get<Renderer>()->SetRenderer(renderer)->SetDelay(3);
}
void GameSystem::Spawn::SpawnGun(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto& equipment = em.AddEntity(EntityType::EQUIPMENT);
	equipment->SetState(EntityState::NONE);
	equipment->Add<TransformerWithAngle>()
		->Add<Collider>()
		->Add<Imager>()
		->Add<RendererWithAngle>();
	equipment->Get<TransformerWithAngle>()->SetPos(pos)->SetAngle(0.0f);
	equipment->Get<Collider>()->GetHitBox().SetRect(pos.x, pos.y , 100.0f, 50.0f);
	TextureManager& tm=TextureManager::GetInstance();
	equipment->Get<Imager>()->SetTexture(&tm.GetTexture(EntityType::EQUIPMENT, TextureType::NONE));
	equipment->Get<RendererWithAngle>()->SetRenderer(renderer)->SetDelay(3);
}
void GameSystem::Recall::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for(auto& player: em.GetEntity(EntityType::PLAYER))
	{
		auto player_t = player->Get<Transformer>();
		for (auto& bullets : em.GetEntity(EntityType::BULLET))
		{
			auto b_t = bullets->Get<Transformer>();
			float distance = (player_t->GetPos() - b_t->GetPos()).Length();
			if (distance > 20000.0)
			{			
				bullets->SetState(EntityState::DEAD);
			}
		}
	}
	for (auto& de : em.GetEntity(EntityType::DEAD_EFFECT))
	{
		if (de->Get<Renderer>()->CheckEndTexture()) de->SetState(EntityState::DEAD);
	}
	for (auto& bullet : em.GetEntity(EntityType::BULLET))
	{
		if(bullet->GetState() == EntityState::DEAD)
			GameSystem::Spawn::DeadEffect(EntityType::BULLET, bullet->Get<Transformer>()->GetPos() - Vec2d<float>{50.0f, 50.0f}, bullet->Get<Renderer>()->GetRenderer());
		
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

}
void GameSystem::HandleControl::Update()
{
	AudioManager& am = AudioManager::GetInstance();
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto& p = e->Get<Physics>();
		auto& c = e->Get<Controller>();
		for (ControlState cs : c->GetState())
		{
			switch (cs)
			{
			case ControlState::NONE:
				break;
			case ControlState::ATTACK:
				break;
			case ControlState::JUMP:
				p->IncreaseForce({ 0.0,-10.0 });
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
				Vec2d<float> vel = mouse.GetRealPos() - col->GetHitBox().GetRect().GetMidPos();
				vel.Normalize();
				//p->IncreaseForce(vel * -1 );
				GameSystem::Spawn::Bullet(col->GetHitBox().GetRect().GetMidPos() + (vel * std::max(col->GetHitBox().GetRect().w, col->GetHitBox().GetRect().h)),
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
				p->IncreaseForce({ 0.0,-10.0 });
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
		auto t = e->Get<Transformer>();
		if (t->GetOnGround())
		{
			p->Get<Reaction>()
				->SetAcceleration(p->Get<Gravity>()->GetAcceleration());
		}
		else
		{
			p->Get<Reaction>()
				->SetAcceleration(0.0);
		}
		
		p->Update();
		
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto p = e->Get<Physics>();
		auto t = e->Get<Transformer>();
		if (t->GetOnGround())
		{
			p->Get<Reaction>()
				->SetAcceleration(p->Get<Gravity>()->GetAcceleration())
				->SetVelocity(p->Get<Gravity>()->GetVeclocity() * -1.0);
		}
		else
		{
			p->Get<Reaction>()
				->SetAcceleration(0.0);
		}
		p->Update();
	}
	for (auto& e : em.GetEntity(EntityType::BULLET))
	{
		auto p = e->Get<Physics>();
		
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
		auto& e_equip = e->Get<Equipments>();
		if (e_equip->GetCurrentId() != -1)
		{
			auto& equipment = em.GetEntity(EntityType::EQUIPMENT).at(e_equip->GetCurrentId());
			const Vec2d<float>& mid_pos = e->Get<Collider>()->GetHitBox().GetRect().GetMidPos();
			equipment->Get<TransformerWithAngle>()->SetPos({mid_pos.x-25.0f,mid_pos.y-25.0f});
			equipment->Get<TransformerWithAngle>()->SetAngle(GetAngle(mouse.GetRealPos() - mid_pos));
		}

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
		auto t = e->Get<Transformer>();
		auto p = e->Get<Physics>();
		t->Increase(p->GetVelocity());
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
		auto bullet_t = bullet->Get<Transformer>();
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
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();

			ground_col->GetHitBox().SetRect(ground_t->GetPos().y, ground_t->GetPos().x, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);

			if (ground_col->GetHitBox().CollideDetect(bullet_col->GetHitBox()))
			{
				bullet->SetState(EntityState::DEAD);
			}
		}
		
	}
	// player vs ground
	for (auto& player : em.GetEntity(EntityType::PLAYER))
	{
		auto player_col = player->Get<Collider>();
		auto player_t = player->Get<Transformer>();
		player_col->GetHitBox().SetRect(player_t->GetPos().y, player_t->GetPos().x, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		auto player_p = player->Get<Physics>();
		const auto& player_v = player_p->GetVelocity();
		bool temp{ false };
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();
			
			ground_col->GetHitBox().SetRect(ground_t->GetPos().y, ground_t->GetPos().x, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);	
			if (ground_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
			{
				Rectangle overlab = ground_col->GetHitBox().GetOverlab(player_col->GetHitBox());
				auto& ground_rect = ground_col->GetHitBox().GetRect();
				auto& player_rect = player_col->GetHitBox().GetRect();
				if (player_rect.GetBottom() - player_v.y - 1.0f <= ground_rect.GetTop())//player o tren ground
				{	
					player_p->SetForce({ player_p->GetForce().x,0.0f });
					temp = true;
					break;
				}
				else if (player_rect.GetTop() - player_v.y >= ground_rect.GetBottom())//player o duoi ground
				{
					player_t->Increase({ 0.0,overlab.h  });
					player_p->SetForce({player_p->GetForce().x,0.0f});
				}			
			}
		
		}
		player_t->SetOnGround(temp);
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();

			ground_col->GetHitBox().SetRect(ground_t->GetPos().y, ground_t->GetPos().x, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);

			if (ground_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
			{
				Rectangle overlab = ground_col->GetHitBox().GetOverlab(player_col->GetHitBox());
				auto& ground_rect = ground_col->GetHitBox().GetRect();
				auto& player_rect = player_col->GetHitBox().GetRect();
				
				if (player_rect.GetBottom() - player_v.y - 1.0f <= ground_rect.GetTop()) player_t->Decrease({ 0.0,overlab.h });
				else
				{
					if (player_t->GetOnGround())
					{
						if(player_rect.GetBottom() <= ground_rect.GetMidPos().y - ground_rect.h/6.0) player_t->Decrease({ 0.0,overlab.h });
					}
					if (player_rect.GetLeft() - player_v.x >= ground_rect.GetRight()) //player o ben phai ground
					{
						player_t->Increase({ overlab.w,0.0 });
					}
					else if (player_rect.GetRight() - player_v.x <= ground_rect.GetLeft()) //player o ben trai ground
					{
						player_t->Decrease({ overlab.w ,0.0 });
					}
				}
				
			}
		}

	}

	for (auto& player : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto player_col = player->Get<Collider>();
		auto player_t = player->Get<Transformer>();
		player_col->GetHitBox().SetRect(player_t->GetPos().y, player_t->GetPos().x, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		auto player_p = player->Get<Physics>();
		const auto& player_v = player_p->GetVelocity();
		bool temp{ false };
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();
			ground_col->GetHitBox().SetRect(ground_t->GetPos().y, ground_t->GetPos().x, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);
			if (ground_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
			{
				Rectangle overlab = ground_col->GetHitBox().GetOverlab(player_col->GetHitBox());
				auto& ground_rect = ground_col->GetHitBox().GetRect();
				auto& player_rect = player_col->GetHitBox().GetRect();
				std::cout << player_v.y << std::endl;
				if (player_rect.GetBottom() - player_v.y*1.1 <= ground_rect.GetTop())//player o tren ground
				{
					player_p->SetForce({ player_p->GetForce().x,0.0f });
					temp = true;
					break;
				}
				else if (player_rect.GetTop() - player_v.y*1.1 >= ground_rect.GetBottom())//player o duoi ground
				{
					player_t->Increase({ 0.0,overlab.h });
					player_p->SetForce({ player_p->GetForce().x,0.0f });
				}
			}
		}
		player_t->SetOnGround(temp);
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();
			ground_col->GetHitBox().SetRect(ground_t->GetPos().y, ground_t->GetPos().x, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);
			if (ground_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
			{
				Rectangle overlab = ground_col->GetHitBox().GetOverlab(player_col->GetHitBox());
				auto& ground_rect = ground_col->GetHitBox().GetRect();
				auto& player_rect = player_col->GetHitBox().GetRect();

				if (player_rect.GetBottom() - player_v.y <= ground_rect.GetTop()) player_t->Decrease({ 0.0,overlab.h });
				else
				{
					if (player_t->GetOnGround())
					{
						if (player_rect.GetBottom() <= ground_rect.GetMidPos().y - ground_rect.h / 6.0) player_t->Decrease({ 0.0,overlab.h });
					}
					if (player_rect.GetLeft() - player_v.x  >= ground_rect.GetRight()) //player o ben phai ground
					{
						player_t->Increase({ overlab.w,0.0 });
					}
					else if (player_rect.GetRight() - player_v.x <= ground_rect.GetLeft()) //player o ben trai ground
					{
						player_t->Decrease({ overlab.w ,0.0 });
					}
				}

			}

		}

	}
	//player vs equipments
	for (auto& player : em.GetEntity(EntityType::PLAYER))
	{
		auto player_col = player->Get<Collider>();
		auto player_t = player->Get<Transformer>();
		player_col->GetHitBox().SetRect(player_t->GetPos().y, player_t->GetPos().x, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		auto& vec_e = em.GetEntity(EntityType::EQUIPMENT);
		for (int i=0;i<vec_e.size();i++ )
		{
			auto equipment_col = vec_e[i]->Get<Collider>();
			auto equipment_t = vec_e[i]->Get<TransformerWithAngle>();
			equipment_col->GetHitBox().SetRect(equipment_t->GetPos().y, equipment_t->GetPos().x, equipment_col->GetHitBox().GetRect().w, equipment_col->GetHitBox().GetRect().h);
			if (vec_e[i]->GetState() == EntityState::NONE)
			{
				if (equipment_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
				{
					player->Get<Equipments>()->Loot(i)->SetCurrentId(i);
					vec_e[i]->SetState(EntityState::EQUIPED);
				}

			}
		}
		
	}
}
void GameSystem::Assets::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	TextureManager& tm = TextureManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto& cs = e->Get<Controller>()->GetState();
		auto& img = e->Get<Imager>();
		img->SetTextureType(TextureType::NONE);
		if(!cs.empty())
		{
			switch (cs[cs.size() - 1])
			{
			case ControlState::JUMP:
				img->SetTextureType(TextureType::JUMP);
				break;
			case ControlState::RUN_LEFT:
				img->SetTextureType(TextureType::RUN_LEFT);
				break;
			case ControlState::RUN_RIGHT:
				img->SetTextureType(TextureType::RUN_RIGHT);
				break;
			case ControlState::FALL:
				img->SetTextureType(TextureType::FALL);
				break;
			}
		}
		img->SetTexture(&tm.GetTexture(e->GetType(), img->GetTextureType()));

	}
}
void GameSystem::Render::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::BACK_GROUND))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x/15.0f) * scale,(pos.y - g_pos.y/15.0f) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
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
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::EQUIPMENT))
	{
		auto r = e->Get<RendererWithAngle>();
		auto pos = e->Get<TransformerWithAngle>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture());
		r->SetAngle(e->Get<TransformerWithAngle>()->GetAngle())
			->SetCenter({25.0f*scale,25.0f*scale})
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::BULLET))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::DEAD_EFFECT))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::GROUND))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * 2.0f* scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}	
}

void GameSystem::Equip::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		e->Get<Equipments>()->Update();
	}
}
