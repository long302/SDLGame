#include"GameSystem.h"
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
