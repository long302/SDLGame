#include"GameSystem.h"

void GameSystem::Assets::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	TextureManager& tm = TextureManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto cs = e->Get<Controller>()->GetState();
		auto img = e->Get<Imager>();
		img->SetTextureType(TextureType::NONE);
		if (!cs.empty())
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