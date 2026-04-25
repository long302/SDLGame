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
	Vec2d<float> max_f{1e9,1e9};
	
public:
	static constexpr ComponentType type = ComponentType::PHYSIC;
	Physics() {};
	~Physics() override ;

	Physics* SetForce(const Vec2d<float>& f) { this->f = f; return this; }
	Physics* SetWeight(float m) { weight.SetVal(m); return this; }
	Physics* SetMaxF(const Vec2d<float>& f) { this->max_f = f; return this; }
	Physics* IncreaseForce(const Vec2d<float>& f) { this->f+=f; return this; }
	const Mess& GetWeight() const { return weight; }
	const Vec2d<float>& GetForce() const { return f; }
	const Vec2d<float>& GetVelocity() const { return v; }
	ComponentType GetType() override { return type; }
	template<typename N>
	Physics* Add()
	{
		physics[N::type] = PhysicPointer(new N);
		return this;

	}
	template<typename N>
	std::shared_ptr<N> Get()
	{
		//debuger
		if (physics.find(N::type) == physics.end())
		{
			std::cout << GetStringOf(type) << " didnt init " << GetStringOf(N::type) << std::endl;
			__debugbreak();
			return nullptr;
		}
		if (strcmp(typeid(N).name(), typeid(*physics[N::type]).name()) != 0)
		{
			std::cout << GetStringOf(type) << " doesnt have " << typeid(N).name() << ", must be " << typeid(*physics[N::type]).name() << std::endl;
			__debugbreak();
			return nullptr;
		}
		//end debuger
		return std::dynamic_pointer_cast<N>(physics[N::type]);

	}
	void Update() override;

};

