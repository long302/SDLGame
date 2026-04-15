#include "Physics.h"
 
		
void Physics::Update()
{
	const Vec2d<float> old_v = v;
	for (auto p : physics)
	{
		p.second->Update(weight);
		f += p.second->GetForce();
	}
	if (abs(f.x) > 10.0)
	{
		if (f.x < 0.0) f.x = -10.0;
		if (f.x > 0.0) f.x = 10.0;
	}
	if (abs(f.y) > 10.0)
	{
		if (f.y < 0.0) f.y = -10.0;
		if (f.y > 0.0) f.y = 10.0;
	}
	v = f/weight.GetVal();
	if ((v.x <= 0.0 && old_v.x>=0.0) || (v.x >= 0.0 && old_v.x <= 0.0))
	{
		
		f.x = 0.0;
		if (physics.find(PhysicType::DRAG) != physics.end())
		{
			physics[PhysicType::DRAG]->SetAcceleration(0.0);
		}
	}
	if (physics.find(PhysicType::DRAG) != physics.end())
	{
		physics[PhysicType::DRAG]->SetVelocity({-v.x,0.0});
		//std::cout << v.x << " " << v.y << " " << physics[PhysicType::DRAG]->GetAcceleration() << std::endl;
	}
	if (physics.find(PhysicType::MOVE) != physics.end())
	{
		physics[PhysicType::MOVE]->SetVelocity({ 0.0,0.0 })->SetAcceleration(0.0f);
	}
	
}
