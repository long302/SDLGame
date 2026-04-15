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
	void Update(const Mess& m) override { f = vel * m.GetVal() * a; vel.Normalize(); }
};

class Drag : public BasePhysic
{
private:
public:
	static constexpr PhysicType type = PhysicType::DRAG;
	Drag() { }
	~Drag() {};

	 void Update(const Mess& m) override{ f = vel * m.GetVal() * a; vel.Normalize();}
};
class Movement:public BasePhysic
{
private:
	float speed{};
public:
	static constexpr PhysicType type = PhysicType::MOVE;
	Movement() {}
	~Movement() {}
	Movement* SetSpeed(float s) { speed = s; return this; }
	float GetSpeed() const { return speed; }
	void Update(const Mess& m) override { f = vel * m.GetVal() * a; vel.Normalize();}
};

class Reaction :public BasePhysic
{
public:
	static constexpr PhysicType type = PhysicType::REACT;
	Reaction() {}
	~Reaction() {}
	void Update(const Mess& m) override { f = vel * m.GetVal() * a; vel.Normalize(); }
};

