#pragma once
#include"Component.h"
#include"BasePhysic.h"
#include<map>
#define PhysicPointer std::shared_ptr<BasePhysic>
#define PhysicMap std::map<PhysicType,PhysicPointer>
class Physics: public Component
{
private:
	Vec2d<float> f{0.0,0.0};
	Vec2d<float> v{ 0.0,0.0 };
	PhysicMap physics;
	Mess weight;
	
public:
	static constexpr ComponentType type = ComponentType::PHYSIC;
	Physics() {};
	~Physics() {};

	Physics* SetForce(const Vec2d<float>& f) { this->f = f; return this; }
	Physics* SetWeight(float m) { weight.SetVal(m); return this; }
	Physics* IncreaseForce(const Vec2d<float>& f) { this->f+=f; return this; }
	const Mess& GetWeight() const { return weight; }
	const Vec2d<float>& GetForce() const { return f; }
	const Vec2d<float>& GetVelocity() const { return v; }
	template<typename N>
	Physics* Add()
	{
		physics[N::type] = PhysicPointer(new N);
		return this;

	}
	template<typename N>
	std::shared_ptr<N> Get()
	{
		if (physics.find(N::type) == physics.end())
		{
			__debugbreak();
			return nullptr;
		}
		return std::dynamic_pointer_cast<N>(physics[N::type]);

	}
	void Update() override;

};

