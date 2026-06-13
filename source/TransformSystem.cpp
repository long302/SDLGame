#include"GameSystem.h"

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
			equipment->Get<TransformerWithAngle>()->SetPos({ mid_pos.x - 25.0f,mid_pos.y - 25.0f });
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
		auto t = e->Get<TransformerWithAngle>();
		auto p = e->Get<Physics>();
		t->Increase(p->GetVelocity());
		t->SetAngle(GetAngle(p->GetVelocity()));
		t->Update();
	}


}