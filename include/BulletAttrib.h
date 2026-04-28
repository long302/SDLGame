#pragma once
#include"Component.h"

class BulletAttrib : public Component
{
private:
	int damage{ 0 };
	EntityType bullet_type{ EntityType::LASER_BULLET };
public:
	constexpr static ComponentType type = ComponentType::ATTRIB;
	BulletAttrib() {};
	~BulletAttrib() {};

	BulletAttrib* SetBulletType(EntityType type) { this->bullet_type = type; return this; }
	BulletAttrib* SetDamage(int damage) { this->damage = damage; return this; }

	int GetDamage() const { return damage; }
	ComponentType GetType() override { return type; }
	EntityType GetBulletType() const { return bullet_type; }

	void Update() override {}
};