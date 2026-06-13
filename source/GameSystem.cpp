#include "GameSystem.h"
void GameSystem::Equip::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	AudioManager& am = AudioManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		e->Get<Equipments>()->Update();
		for(ControlState cs: e->Get<Controller>()->GetState())
		{
			switch(cs)
			{
			
			}
		}
	}
}
