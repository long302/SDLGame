#pragma once
#include"Component.h"

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
	Rectangle rect;
	Rectangle old_rect;
	
public:

	HitBox* SetRect(float top,float left,float w, float h) { this->rect = {left,top,w,h}; return this; }
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
	Rectangle GetOverlab(const HitBox& hb)
	{
		float top = std::max(rect.GetTop(), hb.GetRect().GetTop());
		float left = std::max(rect.GetLeft(), hb.GetRect().GetLeft());
		float right = std::min(rect.GetRight(), hb.GetRect().GetRight());
		float bottom = std::min(rect.GetBottom(), hb.GetRect().GetBottom());
		return { left,top,(float)(right - left),(float)(bottom - top) };
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