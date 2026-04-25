
#pragma once
#define WIDTH 1500
#define HEIGHT 750
#define M_PI 3.14159265358979323846
#include<math.h>
#include<cmath>
#include<string_view>

enum class EntityType
{
	NONE,
	PLAYER,
	NORMAL_ENERMY,
	BULLET,
	GROUND,
	BACK_GROUND,
	DEAD_EFFECT,
	EQUIPMENT
};
	constexpr std::string_view GetStringOf(EntityType type)noexcept
	{
		switch (type)
		{
		case EntityType::NONE:   return "EntityType::NONE";
		case EntityType::PLAYER: return "EntityType::PLAYER";
		case EntityType::NORMAL_ENERMY:  return "EntityType::NORMAL_ENEMY";
		case EntityType::BULLET: return "EntityType::BULLET";
		case EntityType::GROUND: return "EntityType::GROUND";	
		case EntityType::BACK_GROUND: return "EntityType::BACK_GROUND";
		case EntityType::DEAD_EFFECT: return "EntityType::DEAD_EFFECT";
		case EntityType::EQUIPMENT: return "EntityType::EQUIPMENT";
		default: return "Unknown";
		}
	}
enum class EntityState
{
	NONE,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP,
	FALL,
	STUN,
	ACTIVE_SKILL_1,
	DEAD,
	EQUIPED,
	LOOTED
};
template<typename N>
class Vec2d
{
public:
	N x{};
	N y{};

	Vec2d() = default;
	Vec2d(N x, N y) { this->x = x; this->y = y; }
	~Vec2d() = default;

	Vec2d& SetX(N x)
	{
		this->x = x;
		return *this;
	}
	Vec2d& SetY(N y)
	{
		this->y = y;
		return *this;
	}
	Vec2d operator +(const Vec2d& v) const
	{
		return { x + v.x, y + v.y };
	}
	Vec2d& operator +=(const Vec2d& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2d operator -(const Vec2d& v) const
	{
		return { x - v.x, y - v.y };
	}
	Vec2d& operator -=(const Vec2d& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2d operator*(N val) const
	{
		return { x * val, y * val };
	}
	Vec2d& operator*=(N val)
	{	
		x *= val;
		y *= val;
		return *this;
	}
	Vec2d operator/(N val) const
	{
		return { x / val,y / val };
	}
	Vec2d& operator/=(N val)
	{
		x /= val;
		y /= val;
		return *this;
	}
	Vec2d& operator=(const Vec2d& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	float Length() const
	{
		return std::sqrt(x * x + y * y);
	}
	Vec2d& Normalize()
	{
		float len = Length();

		if (len == 0) return *this;

		x /= len;
		y /= len;
		return *this;
	}
};
static double GetAngle(const Vec2d<float>& v)
{
	double angle = (double)atan2(v.y, v.x) * 180.0 / M_PI;
	if (angle < 0) angle += 360.0;
	return angle;
}
extern Vec2d<float> size_screen;
extern Vec2d<float> g_pos;
extern float scale;