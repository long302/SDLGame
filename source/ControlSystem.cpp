#include"GameSystem.h"

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
	static int count_swap = 0;
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

				if (e->Get<Equipments>()->CanUse())
				{
					auto& equipment = em.GetEntity(EntityType::EQUIPMENT)[e->Get<Equipments>()->GetCurrentId()];
					auto equip_attrib = equipment->Get<EquipmentAttrib>();
					auto equip_col = equipment->Get<Collider>();
					auto equip_r = equipment->Get<RendererWithAngle>();
					auto equip_t = equipment->Get<TransformerWithAngle>();
					Vec2d<float> vec = { equip_col->GetHitBox().GetRect().w + 30.0f, equip_col->GetHitBox().GetRect().h / 2.0f };
					Vec2d<float> bullet_mid_pos = equip_t->GetPos() + vec;
					Vec2d<float> equipment_mid_pos = equip_col->GetHitBox().GetRect().GetMidPos();

					bullet_mid_pos.Rolate(equip_r->GetAngle(), equip_t->GetPos() + Vec2d<float>{25.0f, 25.0f});
					equipment_mid_pos.Rolate(equip_r->GetAngle(), equip_t->GetPos() + Vec2d<float>{25.0f, 25.0f});
					switch (equip_attrib->GetBulletType())
					{
					case EntityType::LASER_BULLET:
						GameSystem::Spawn::LaserBullet(bullet_mid_pos, equip_r->GetRenderer(), (bullet_mid_pos - equipment_mid_pos).Normalize());
						break;
					case EntityType::ROCKET_BULLET:
						GameSystem::Spawn::RocketBullet(bullet_mid_pos, equip_r->GetRenderer(), (bullet_mid_pos - equipment_mid_pos).Normalize());
						break;
					}
					am.PlayAudio(EntityType::PLAYER, AudioType::SHOOT);
				}
				break;
			case ControlState::SWAP_WEAPON:
				
				if (e->Get<Equipments>()->CanUse()&&count_swap++%10==0)
				{
					em.GetEntity(EntityType::EQUIPMENT)[e->Get<Equipments>()->GetCurrentId()]->SetState(EntityState::LOOTED);
					e->Get<Equipments>()->SwapWeapon();
					em.GetEntity(EntityType::EQUIPMENT)[e->Get<Equipments>()->GetCurrentId()]->SetState(EntityState::EQUIPED);
					if(e->Get<Equipments>()->GetIds().size() > 1) am.PlayAudio(EntityType::PLAYER, AudioType::SWAP_WEAPON);
				}
				break;
			case ControlState::REMOVE_WEAPON:
				if (e->Get<Equipments>()->CanUse())
				{
					em.GetEntity(EntityType::EQUIPMENT)[e->Get<Equipments>()->GetCurrentId()]->SetState(EntityState::NONE);
				}
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