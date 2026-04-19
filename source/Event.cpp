#include "Event.h"

SDL_Event event;
Mouse mouse;
KeyBoard key_board;

Mouse::Mouse()
{
	state = SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
}
void Mouse::Update()
{
	Vec2d<float> old_pos = screen_pos;
	state = SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	if (GetRightState())
	{
		g_pos -= (screen_pos - old_pos)/scale;
	}
	real_pos = g_pos + screen_pos / scale;
}
KeyBoard::KeyBoard()
{
	state = SDL_GetKeyboardState(NULL);
}

