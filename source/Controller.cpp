#include "Controller.h"
void Controller::Update()
{	
	state.clear();
	if (key_board.GetState(Keys::KEY_A)) state.push_back( ControlState::RUN_LEFT);
	if (key_board.GetState(Keys::KEY_D)) state.push_back(ControlState::RUN_RIGHT);
	if (key_board.GetState(Keys::KEY_SPACE)) state.push_back(ControlState::JUMP);
	if (key_board.GetState(Keys::KEY_F)) state.push_back(ControlState::LOOT);
	if (key_board.GetState(Keys::KEY_R)) state.push_back(ControlState::REMOVE_WEAPON);
	if (key_board.GetState(Keys::KEY_Q)) state.push_back(ControlState::SWAP_WEAPON);
	if (mouse.GetLeftState()) state.push_back(ControlState::USING_SK1);
	
	mouse.Update();
}
