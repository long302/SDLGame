#include"GameSystem.h"

void GameSystem::Recall::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for (auto& player : em.GetEntity(EntityType::PLAYER))
	{
		auto player_t = player->Get<Transformer>();
		for (auto& bullets : em.GetEntity(EntityType::BULLET))
		{
			auto b_t = bullets->Get<TransformerWithAngle>();
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
		if (bullet->GetState() == EntityState::DEAD)
			GameSystem::Spawn::DeadEffect(bullet->Get<BulletAttrib>()->GetBulletType(), bullet->Get<Collider>()->GetHitBox().GetRect().GetMidPos(), bullet->Get<RendererWithAngle>()->GetRenderer());

	}

	em.DeleteDeadEntity();

}