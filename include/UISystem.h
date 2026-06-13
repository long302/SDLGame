#pragma once
#include<SDL3_ttf/SDL_ttf.h>
#include"Event.h"
#include"Component.h"
#include"MapMethods.h"
enum class UIType
{
	NONE,
	HOME,
	PLAY_GAME,
	SETTING,
	INSTRUMENT,
	LOAD_MAP,
	ADD_MAP,
	IN_GAME
};
enum class UIState
{
	NONE,
	CHANGE,
	HIDE
};
extern UIState us;
extern std::string mapChoosen;
class UIControl
{
private:
	std::vector<UIType> ui_stack{UIType::HOME};

	UIControl() = default;
public:
	~UIControl() = default;
	const std::vector<UIType>& GetUIStack() { return ui_stack; }
	void ChangeUI(UIType ui_type) { ui_stack.push_back(ui_type); us = UIState::CHANGE; }
	UIType GetCurrentUI() const { return ui_stack.back(); }
	void BackUI() { if (ui_stack.size() > 1) ui_stack.pop_back(); us = UIState::CHANGE; }
	static UIControl& GetInstance()
	{
		static UIControl instance;
		return instance;
	}
	UIControl(const UIControl&) = delete;
};
namespace UISystem
{	
	bool ChangeTo(UIType ui_type, SDL_Renderer* renderer, TTF_TextEngine* engine);
	void Update(SDL_Renderer* renderer, TTF_TextEngine* engine);
}