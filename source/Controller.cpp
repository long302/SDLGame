#include "Controller.h"
void Controller::Update()
{
	state.clear();
	if (key_board.GetState(Keys::KEY_A)) state.push_back( ControlState::RUN_LEFT);
	if (key_board.GetState(Keys::KEY_D)) state.push_back(ControlState::RUN_RIGHT);
	if (key_board.GetState(Keys::KEY_SPACE)) state.push_back(ControlState::JUMP);
	if (mouse.GetLeftState()) state.push_back(ControlState::USING_SK1);
	
	mouse.Update();
}
