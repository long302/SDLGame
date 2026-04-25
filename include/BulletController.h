#pragma once
#include"Component.h"

class BulletController: public Component
{
private:
	Vec2d<float> vel{};
public:
	static constexpr ComponentType type = ComponentType::CONTROL;
	BulletController() {};
	~BulletController() {};
	BulletController* SetVelocity(const Vec2d<float>& v) { vel = v; return this; }
	const Vec2d<float>& GetVelocity() const { return vel; }
	ComponentType GetType() override { return type; }
	void Update() override {  }

};