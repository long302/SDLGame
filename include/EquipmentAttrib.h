#pragma once
#include"Component.h"


class EquipmentAttrib : public Component
{
private:
	int damage{ 0 };
	EntityType equipment_type{ EntityType::LASER_GUN };
	EntityType bullet_type{ EntityType::LASER_BULLET };
public:
	constexpr static ComponentType type = ComponentType::ATTRIB;
	EquipmentAttrib() {};
	~EquipmentAttrib() {};

	EquipmentAttrib* SetBulletType(EntityType type) { this->bullet_type = type; return this; }
	EquipmentAttrib* SetEquipmentType(EntityType type) { this->equipment_type = type; return this; }
	EquipmentAttrib* SetDamage(int damage) { this->damage = damage; return this; }

	int GetDamage() const { return damage; }
	ComponentType GetType() override { return type; }
	EntityType GetBulletType() const { return bullet_type; }
	EntityType GetEquipmentType() const { return equipment_type; }

	void Update() override {}	

};