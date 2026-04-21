#include "Physics.h"
 
		
Physics::~Physics()
{
	physics.clear();
	//std::cout << "Physic clear\n";
}

void Physics::Update()
{
	for (auto p : physics)
	{
		p.second->Update(weight);
		f += p.second->GetForce();
	}
	if (abs(f.x) > max_f.x)
	{
		if (f.x < 0.0) f.x = -max_f.x;
		if (f.x > 0.0) f.x = max_f.x;
	}
	if (abs(f.y) > max_f.y)
	{
		if (f.y < 0.0) f.y = -max_f.y;
		if (f.y > 0.0) f.y = max_f.y;
	}
	v = f/weight.GetVal();
	if (physics.find(PhysicType::DRAG) != physics.end())
	{
		physics[PhysicType::DRAG]->SetVelocity({-v.x,0});
		physics[PhysicType::DRAG]->SetAcceleration(0.3);
		if (abs(v.x) < 0.4) v.x = 0.0f;
		
	//	std::cout << v.x << " " << v.y << " " << physics[PhysicType::DRAG]->GetAcceleration() << std::endl;
	}
	if (physics.find(PhysicType::REACT) != physics.end())
	{
		
	}
	if (physics.find(PhysicType::MOVE) != physics.end())
	{
		physics[PhysicType::MOVE]->SetVelocity({ 0.0,0.0 })->SetAcceleration(0.0f);
	}
	
}
