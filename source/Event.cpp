#include "Event.h"

SDL_Event event;
GameMode mode = GameMode::Viewer;
Mouse mouse;
KeyBoard key_board;

Mouse::Mouse()
{
	state = SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
}
Vec2d<float> Mouse::GetChange()
{
	return screen_pos - old_pos;
}
void Mouse::Update()
{
	left_cd.SetPoint2();
	old_pos = screen_pos;
	state = SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	if (GetRightState())
	{
		g_pos -= GetChange()/(scale);
	}
	real_pos = g_pos + screen_pos / scale;
}
KeyBoard::KeyBoard()
{
	state = SDL_GetKeyboardState(NULL);
}

