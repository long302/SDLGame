#include "Event.h"

SDL_Event event;
Mouse mouse;
KeyBoard key_board;

Mouse::Mouse()
{
	state = SDL_GetMouseState(&pos.x, &pos.y);
}
void Mouse::Update()
{
	Vec2d<float> old_pos = pos;
	state = SDL_GetMouseState(&pos.x, &pos.y);
	if (GetRightState())
	{
		g_pos -= (pos - old_pos);
	}
}
KeyBoard::KeyBoard()
{
	state = SDL_GetKeyboardState(NULL);
}

