#pragma once
#include"Component.h"
class Transformer : public Component
{
private:
	Vec2d<float> pos{};
	bool on_ground{};
public:
	constexpr static ComponentType type = ComponentType::TRANSFORM;

	Transformer() = default;
	Transformer(float x, float y)	{ pos.SetX(x).SetY(y); }
	Transformer(const Vec2d<float>& p){ pos=p; }
	~Transformer() = default;

	const Vec2d<float>& GetPos() { return pos; }
	bool GetOnGround() const { return on_ground; }

	Transformer* SetPos(float x, float y) { pos.SetX(x).SetY(y); return this; }
	Transformer* SetPos(const Vec2d<float>& p) { pos = p; return this; }
	
	Transformer* Increase(const Vec2d<float>& vec) { pos += vec; return this; }
	Transformer* Decrease(const Vec2d<float>& vec) { pos -= vec; return this; }

	void Update() override;
};
class BulletTransformer : public Component
{
private:
	Vec2d<float> pos{};
public:
	constexpr static ComponentType type = ComponentType::TRANSFORM;

	BulletTransformer() = default;
	BulletTransformer(float x, float y) { pos.SetX(x).SetY(y); }
	BulletTransformer(const Vec2d<float>& p) { pos = p; }
	~BulletTransformer() = default;

	const Vec2d<float>& GetPos() { return pos; }

	BulletTransformer* SetPos(float x, float y) { pos.SetX(x).SetY(y); return this; }
	BulletTransformer* SetPos(const Vec2d<float>& p) { pos = p; return this; }

	BulletTransformer* Increase(const Vec2d<float>& vec) { pos += vec; return this; }
	BulletTransformer* Decrease(const Vec2d<float>& vec) { pos -= vec; return this; }

	void Update() override {};
};