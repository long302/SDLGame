#pragma once
#include"Component.h"

class BulletController: public Component
{
private:
	Vec2d<float> vel{};
	float speed{ 10.0 };
public:
	static constexpr ComponentType type = ComponentType::CONTROL;
	BulletController() {};
	~BulletController() {};
	BulletController* SetVelocity(const Vec2d<float>& v) { vel = v; return this; }
	BulletController* SetSpeed(float s) { speed = s; return this; }
	const Vec2d<float>& GetVelocity() const { return vel; }
	float GetSpeed() const { return speed; }
	void Update() override { vel.Normalize(); }

};