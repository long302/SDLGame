#pragma once
#include"Component.h"

inline constexpr float TILE_SIZE = 32.0f;
inline constexpr Vec2d<float> PlayerSize = { 100.0f,100.0f };
inline constexpr Vec2d<float> EnermySize = { 100.0f,100.0f };
inline constexpr Vec2d<float> GroundSize = { 400.0f,100.0f };
inline constexpr Vec2d<float> RocketBulletSize = { 100.0f,50.0f };
inline constexpr Vec2d<float> LaserBulletSize = { 25.0f,25.0f };
inline constexpr Vec2d<float> ButtonSize = { 200.0f,50.0f };
inline constexpr Vec2d<float> EquipSize = { 100.0f,50.0f };
inline constexpr Vec2d<float> DeadEffectSize = { 100.0f,100.0f };//can fix later
struct Rectangle
{
	float left, top, w, h;
	float GetLeft() const { return left; }
	float GetRight() const { return left+w; }
	float GetTop() const { return top; }
	float GetBottom() const { return top+h; }
	const Vec2d<float> GetMidPos() const { return { left + w / 2.0f,top + h / 2.0f }; }

};
//hitbox is a rectangle
class HitBox
{
	Rectangle rect{};
	Rectangle old_rect{};
	
public:
	HitBox() {};
	~HitBox() {};
	HitBox* SetRect(float left, float top, float w, float h) { rect.left = left, rect.top = top, rect.w = w, rect.h = h; return this; }
	const Rectangle& GetRect() const { return rect; }
	const Rectangle& GetOldRect() const { return old_rect; }
	HitBox* SetOldRect() { old_rect = rect; return this; }

	bool CollideDetect(const HitBox& hb)
	{
		if (abs(rect.GetMidPos().x - hb.GetRect().GetMidPos().x) <= hb.GetRect().w / 2.0f + rect.w / 2.0f
			&& abs(rect.GetMidPos().y - hb.GetRect().GetMidPos().y) <= hb.GetRect().h / 2.0f + rect.h / 2.0f)
			return true;
		else return false;
	}
	bool CollideDetectPoint(const Vec2d<float>& point)
	{
	
		if (point.x > rect.GetLeft() && point.x < rect.GetRight()
			&& point.y > rect.GetTop() && point.y < rect.GetBottom())
		{
			return true;
		}
		else return false;
	}
	Rectangle GetOverlab(const HitBox& hb)
	{
		float top = std::max(rect.GetTop(), hb.GetRect().GetTop());
		float left = std::max(rect.GetLeft(), hb.GetRect().GetLeft());
		float right = std::min(rect.GetRight(), hb.GetRect().GetRight());
		float bottom = std::min(rect.GetBottom(), hb.GetRect().GetBottom());
		return { left, top, right - left, bottom - top};
	}
};
class Collider: public Component
{
private:
	HitBox hb{};
	
public:
	static constexpr ComponentType type{ ComponentType::COLLIDE };
	Collider() {};
	~Collider() {};
	HitBox& GetHitBox() { return hb; }
	ComponentType GetType() override { return type; }
	void SetOldRect() { hb.SetOldRect(); }
	void Update() override;
};