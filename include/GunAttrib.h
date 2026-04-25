#pragma once
#include"Component.h"

enum class BulletType
{
	LASER,
	ROCKET,
	BOMB
};
class GunAttrib : public Component
{
private:
	int damage{ 0 };
	BulletType bullet_type{ BulletType::LASER };
public:
	GunAttrib() {};
	~GunAttrib() {};
	GunAttrib* SetDamage(int damage) { this->damage = damage; return this; }
	int GetDamage() const { return damage; }
	GunAttrib* SetBulletType(BulletType bullet_type) { this->bullet_type = bullet_type; return this; }
	BulletType GetBulletType() const { return bullet_type; }
	void Update() override	{}

};