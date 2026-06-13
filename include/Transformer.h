#pragma once
#include"Component.h"
class Transformer : public Component
{
protected:
	Vec2d<float> pos{};
	Vec2d<float> old_pos{};

	bool on_ground{false};
public:
	constexpr static ComponentType type = ComponentType::TRANSFORM;

	Transformer() = default;
	Transformer(float x, float y)	{ pos.SetX(x).SetY(y); }
	Transformer(const Vec2d<float>& p){ pos=p; }
	~Transformer() = default;

	ComponentType GetType() override { return type; }
	const Vec2d<float>& GetPos() const { return pos; }
	const Vec2d<float>& GetOldPos() const { return old_pos; }
	bool GetOnGround() const { return on_ground; }
	Transformer* SetOnGround(bool value) { on_ground = value; return this; }

	Transformer* SetPos(float x, float y) { pos.SetX(x).SetY(y); return this; }
	Transformer* SetPos(const Vec2d<float>& p) { pos = p; return this; }
	
	Transformer* UpdateOldPos() { old_pos = pos; return this; }
	Transformer* Increase(const Vec2d<float>& vec) { pos += vec; return this; }
	Transformer* Decrease(const Vec2d<float>& vec) { pos -= vec; return this; }

	void Update() override;
};
class TransformerWithAngle : public Component
{
private:
	Vec2d<float> pos{};
	double angle{ 0.0f };
public:
	constexpr static ComponentType type = ComponentType::TRANSFORM;

	TransformerWithAngle() = default;
	~TransformerWithAngle() = default;

	TransformerWithAngle* SetPos(float x, float y) { pos.SetX(x).SetY(y); return this; }
	TransformerWithAngle* SetPos(const Vec2d<float>& p) { pos = p; return this; }
	TransformerWithAngle* SetAngle(double a) { angle = a; return this; }

	ComponentType GetType() override { return type; }
	const Vec2d<float>& GetPos() { return pos; }
	double GetAngle() const { return angle; }

	TransformerWithAngle* Increase(const Vec2d<float>& vec) { pos += vec; return this; }
	TransformerWithAngle* Decrease(const Vec2d<float>& vec) { pos -= vec; return this; }

	void Update() override {};
};
class TextTransformer : public Transformer
{
private:
	Vec2d<float> text_pos{};
public:
	TextTransformer() {};
	~TextTransformer() {};
	TextTransformer* SetTextPos(float x, float y) { text_pos.SetX(x).SetY(y); return this; }
	TextTransformer* SetTextPos(const Vec2d<float>& p) { text_pos = p; return this; }
	Vec2d<float> GetTextPos() const { return text_pos; }
	TextTransformer* Increase(const Vec2d<float>& vec) { Transformer::pos += vec; text_pos += vec; return this; }
	TextTransformer* Decrease(const Vec2d<float>& vec) { Transformer::pos -= vec; text_pos -= vec; return this; }
	void Update() override {};
};