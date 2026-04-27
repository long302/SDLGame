#pragma once
#include"Component.h"


class EquipmentAttrib : public Component
{
private:
	int damage{ 0 };
	EntityType bullet_type{ EntityType::LASER_BULLET };
public:
	constexpr static ComponentType type = ComponentType::EQUIPMENT_ATTRIB;
	EquipmentAttrib() {};
	~EquipmentAttrib() {};
	ComponentType GetType() override { return type; }
	EquipmentAttrib* SetDamage(int damage) { this->damage = damage; return this; }
	int GetDamage() const { return damage; }
	EquipmentAttrib* SetBulletType(EntityType type) { this->bullet_type = type; return this; }
	EntityType GetBulletType() const { return bullet_type; }
	void Update() override {}	

};