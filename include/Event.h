#pragma once
#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"
#include"SDL3_mixer/SDL_mixer.h"
#include"Vec2d.h"
#include"Timer.h"
#include<iostream>
#include<map>
#include<vector>
extern SDL_Event event;
enum class Keys
{
    KEY_A = 4,
    KEY_B = 5,
    KEY_C = 6,
    KEY_D = 7,
    KEY_E = 8,
    KEY_F = 9,
    KEY_G = 10,
    KEY_H = 11,
    KEY_I = 12,
    KEY_J = 13,
    KEY_K = 14,
    KEY_L = 15,
    KEY_M = 16,
    KEY_N = 17,
    KEY_O = 18,
    KEY_P = 19,
    KEY_Q = 20,
    KEY_R = 21,
    KEY_S = 22,
    KEY_T = 23,
    KEY_U = 24,
    KEY_V = 25,
    KEY_W = 26,
    KEY_X = 27,
    KEY_Y = 28,
    KEY_Z = 29,

    KEY_1 = 30,
    KEY_2 = 31,
    KEY_3 = 32,
    KEY_4 = 33,
    KEY_5 = 34,
    KEY_6 = 35,
    KEY_7 = 36,
    KEY_8 = 37,
    KEY_9 = 38,
    KEY_0 = 39,

    KEY_F1 = 58,
    KEY_F2 = 59,
    KEY_F3 = 60,
    KEY_F4 = 61,
    KEY_F5 = 62,
    KEY_F6 = 63,
    KEY_F7 = 64,
    KEY_F8 = 65,
    KEY_F9 = 66,
    KEY_F10 = 67,
    KEY_F11 = 68,
    KEY_F12 = 69,

    KEY_ESCAPE = 41,
    KEY_BACKSPACE = 42,
    KEY_TAB = 43,
    KEY_SPACE = 44,

    KEY_LCTRL = 224
};
class Mouse
{
private:
    Vec2d<float> screen_pos{};
    Vec2d<float> real_pos{};
    Uint32 state{};
public:
    Mouse();
    ~Mouse() = default;
    const Vec2d<float>& GetScreenPos() const { return screen_pos; }
    const Vec2d<float> GetRealPos() const { return real_pos; }
    const bool GetLeftState() const { return state & SDL_BUTTON_LMASK; }
    const bool GetRightState() const { return state & SDL_BUTTON_RMASK; }
    const bool GetMidState() const { return state & SDL_BUTTON_MMASK; }

    void Update();
};
extern Mouse mouse;
class KeyBoard
{
private:
    const bool* state;
public:
    KeyBoard();
    ~KeyBoard() = default;

    const bool GetState(Keys key) const { return state[static_cast<int>(key)]; }
};
extern KeyBoard key_board;
