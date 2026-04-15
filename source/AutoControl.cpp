#include"AutoControl.h"


void AutoControl::Update()
{
	state.clear();
	if(steps--<0) 
	{
		rand_nums = std::rand() % 4;
		steps = std::rand() % 100;
	}

	switch (rand_nums)
	{
	case 0:
		state.push_back(ControlState::RUN_LEFT);
		break;
	case 1:
		state.push_back(ControlState::RUN_RIGHT);
		break;
	case 2:
		state.push_back(ControlState::JUMP);
		break;
	case 3:
		break;
	}
}