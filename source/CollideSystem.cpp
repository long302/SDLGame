#include"GameSystem.h"

void GameSystem::Collide::Update()
{
	
	EntityManager& em = EntityManager::GetInstance();
	for (auto& ground : em.GetEntity(EntityType::GROUND))
	{
		auto ground_col = ground->Get<Collider>();
		auto ground_t = ground->Get<Transformer>();

		ground_col->GetHitBox().SetRect(ground_t->GetPos().x, ground_t->GetPos().y, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);
	}
	//player with normal enermy
	for (auto& player : em.GetEntity(EntityType::PLAYER))
	{
		auto player_col = player->Get<Collider>();
		auto player_t = player->Get<Transformer>();
		player_col->GetHitBox().SetRect(player_t->GetPos().x, player_t->GetPos().y, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		for (auto& normal_enermy : em.GetEntity(EntityType::NORMAL_ENERMY))
		{
			auto ne_col = normal_enermy->Get<Collider>();
			auto ne_t = normal_enermy->Get<Transformer>();
			ne_col->GetHitBox().SetRect(ne_t->GetPos().x, ne_t->GetPos().y, ne_col->GetHitBox().GetRect().w, ne_col->GetHitBox().GetRect().h);
			if (player_col->GetHitBox().CollideDetect(ne_col->GetHitBox()))
			{
				const Rectangle& rect = player_col->GetHitBox().GetOverlab(ne_col->GetHitBox());

				if (rect.GetMidPos().x < ne_col->GetHitBox().GetRect().GetMidPos().x)
				{
					ne_t->Increase({ rect.w / 8.0f,0 });
				}
				else
				{
					ne_t->Decrease({ rect.w / 8.0f,0 });
				}
			}
		}
	}
	//bullet with all
	for (auto& bullet : em.GetEntity(EntityType::BULLET))
	{
		auto& bullet_col = bullet->Get<Collider>();
		auto bullet_t = bullet->Get<TransformerWithAngle>();
		bullet_col->GetHitBox().SetRect(bullet_t->GetPos().x, bullet_t->GetPos().y, bullet_col->GetHitBox().GetRect().w, bullet_col->GetHitBox().GetRect().h);
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

			ground_col->GetHitBox().SetRect(ground_t->GetPos().x, ground_t->GetPos().y, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);

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
		player_col->GetHitBox().SetRect(player_t->GetPos().x, player_t->GetPos().y, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		auto player_p = player->Get<Physics>();
		const auto& player_v = player_p->GetVelocity();
		bool temp{ false };
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();

			ground_col->GetHitBox().SetRect(ground_t->GetPos().x, ground_t->GetPos().y, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);
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

			ground_col->GetHitBox().SetRect(ground_t->GetPos().x, ground_t->GetPos().y, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);

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
						if (player_rect.GetBottom() <= ground_rect.GetMidPos().y - ground_rect.h / 6.0) player_t->Decrease({ 0.0,overlab.h });
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
		player_col->GetHitBox().SetRect(player_t->GetPos().x, player_t->GetPos().y, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		auto player_p = player->Get<Physics>();
		const auto& player_v = player_p->GetVelocity();
		bool temp{ false };
		for (auto& ground : em.GetEntity(EntityType::GROUND))
		{
			auto ground_col = ground->Get<Collider>();
			auto ground_t = ground->Get<Transformer>();
			ground_col->GetHitBox().SetRect(ground_t->GetPos().x, ground_t->GetPos().y, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);
			if (ground_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
			{
				Rectangle overlab = ground_col->GetHitBox().GetOverlab(player_col->GetHitBox());
				auto& ground_rect = ground_col->GetHitBox().GetRect();
				auto& player_rect = player_col->GetHitBox().GetRect();
				std::cout << player_v.y << std::endl;
				if (player_rect.GetBottom() - player_v.y * 1.1 <= ground_rect.GetTop())//player o tren ground
				{
					player_p->SetForce({ player_p->GetForce().x,0.0f });
					temp = true;
					break;
				}
				else if (player_rect.GetTop() - player_v.y * 1.1 >= ground_rect.GetBottom())//player o duoi ground
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
			ground_col->GetHitBox().SetRect(ground_t->GetPos().x, ground_t->GetPos().y, ground_col->GetHitBox().GetRect().w, ground_col->GetHitBox().GetRect().h);
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
	//player vs equipments
	for (auto& player : em.GetEntity(EntityType::PLAYER))
	{
		auto player_col = player->Get<Collider>();
		auto player_t = player->Get<Transformer>();
		player_col->GetHitBox().SetRect(player_t->GetPos().x, player_t->GetPos().y, player_col->GetHitBox().GetRect().w, player_col->GetHitBox().GetRect().h);
		auto& player_e = player->Get<Equipments>();
		auto& vec_e = em.GetEntity(EntityType::EQUIPMENT);
		for (int i = 0; i < vec_e.size(); i++)
		{
			auto equipment_col = vec_e[i]->Get<Collider>();
			auto equipment_t = vec_e[i]->Get<TransformerWithAngle>();
			equipment_col->GetHitBox().SetRect(equipment_t->GetPos().x, equipment_t->GetPos().y, equipment_col->GetHitBox().GetRect().w, equipment_col->GetHitBox().GetRect().h);
			if (vec_e[i]->GetState() == EntityState::NONE)
			{
				if (equipment_col->GetHitBox().CollideDetect(player_col->GetHitBox()))
				{
					if (player_e->GetCurrentId() != -1)
					{
						vec_e[player_e->GetCurrentId()]->SetState(EntityState::LOOTED);
					}
					player_e->Loot(i)->SetCurrentId(i);
					vec_e[i]->SetState(EntityState::EQUIPED);
				}
			}
		}

	}
	static int alpha=255;
	
	if (mode == GameMode::Player)
	{
		for (auto& b : em.GetEntity(EntityType::BUTTON_UI))
		{
			auto hb = b->Get<Collider>()->GetHitBox();
			if (mouse.GetScreenPos().x<hb.GetRect().GetRight() && mouse.GetScreenPos().x>hb.GetRect().GetLeft()
				&& mouse.GetScreenPos().y > hb.GetRect().GetTop() && mouse.GetScreenPos().y < hb.GetRect().GetBottom())
			{
				b->Get<Text>()->SetColor(0, 0, 0, 255);
				if (mouse.GetLeftState())
				{
					
				}
				alpha = 255;

			}
			else
			{
				alpha -= 5;
				if (alpha <= 0)
				{
					b->Get<TextRenderer>()->SetDstRect({ 0,0,0,0 });
					alpha = 1;
				}
				b->Get<Text>()->SetColor(255, 0, 0, alpha);
			}
		}
	}
	if (mode == GameMode::Creator)
	{
		for (auto& b : em.GetEntity(EntityType::BUTTON_UI))
		{
			auto& hb = b->Get<Collider>()->GetHitBox();
			auto& t = b->Get<TextTransformer>();
			auto& text = b->Get<Text>();
			int w, h;
			text->GetTextSize(&w, &h);
			hb.SetRect(t->GetPos().x, t->GetPos().y, w * 1.2f, h * 1.2f);
			const Vec2d<float> mid_pos = hb.GetRect().GetMidPos();
			const Vec2d<float> text_pos = mid_pos - Vec2d<float>{w / 2.0f, h / 2.0f};
			b->Get<TextTransformer>()->SetTextPos(text_pos);
		}
	}
}