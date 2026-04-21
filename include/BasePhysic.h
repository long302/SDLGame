#pragma once
#include"Vec2d.h"
enum class PhysicType
{
	GRAVITY,
	JUMP,
	DRAG,
	MOVE,
	REACT
};
constexpr std::string_view GetStringOf(PhysicType type)
{
	switch (type)
	{
	case PhysicType::GRAVITY:  return "PhysicType::GRAVITY";
	case PhysicType::JUMP: return "PhysicType::JUMP";
	case PhysicType::DRAG:  return "PhysicType::DRAG";
	case PhysicType::REACT: return "PhysicType::REACT";
	default: return "Unknown";
	}
}
class Mess
{
private:
	float m{1.0f};
public:
	Mess() {};
	~Mess() {};
	Mess& SetVal(float m) { this->m = m; return *this; }
	float GetVal() const { return m; }
};
class BasePhysic
{
protected:
	Vec2d<float> f{};
	float a{};
	Vec2d<float> vel{};
public:

	BasePhysic() {};
	virtual ~BasePhysic() {};
	virtual PhysicType GetType() =0;
	BasePhysic* SetAcceleration(float a) { this->a = a; return this; }
	BasePhysic* SetVelocity(const Vec2d<float>& vel) { this->vel = vel; return this; }
	//update to get new value
	const Vec2d<float>& GetForce() const { return f; }
	const Vec2d<float>& GetVeclocity() const { return vel; }
	float GetAcceleration() const { return a; }
	virtual void Update(const Mess& m) = 0;
};

class Gravity : public BasePhysic
{
private:
	
public:
	static constexpr PhysicType type = PhysicType::GRAVITY;	
	Gravity() { vel = { 0.0,1.0 }; a = 1.0f; }
	~Gravity() {};
	PhysicType GetType() override { return type; }

	void Update(const Mess& m) override {  vel.Normalize();f = vel * m.GetVal() * a;}
};

class Drag : public BasePhysic
{
private:
public:
	static constexpr PhysicType type = PhysicType::DRAG;
	Drag() { }
	~Drag() {};
	PhysicType GetType() override { return type; }
	 void Update(const Mess& m) override{ vel.Normalize();f = vel * m.GetVal() * a; }
};
class Movement:public BasePhysic
{
private:
	float speed{};
public:
	static constexpr PhysicType type = PhysicType::MOVE;
	Movement() {}
	~Movement() {}
	PhysicType GetType() override { return type; }
	Movement* SetSpeed(float s) { speed = s; return this; }
	float GetSpeed() const { return speed; }
	void Update(const Mess& m) override { vel.Normalize();f = vel * m.GetVal() * a; }
};

class Reaction :public BasePhysic
{
public:
	static constexpr PhysicType type = PhysicType::REACT;
	Reaction() { vel = { 0.0,-1.0 }; a = 0.0f; }
	~Reaction() {}
	PhysicType GetType() override { return type; }
	void Update(const Mess& m) override { vel.Normalize();f = vel * m.GetVal() * a; }
};

