#include "UISystem.h"
UIState us = UIState::NONE;
std::string mapChoosen = "";
bool UISystem::ChangeTo(UIType ui_type, SDL_Renderer* renderer, TTF_TextEngine* engine)
{
	std::cout << "Change UI " << std::endl;
	EntityManager& em = EntityManager::GetInstance();
	em.GetEntity(EntityType::BUTTON_UI).clear();
	switch (ui_type)
	{
	case UIType::HOME:
		Map::LoadUI("ViewMap/Home", renderer, engine);
		break;
	case UIType::PLAY_GAME:
		Map::LoadUI("ViewMap/PlayGame", renderer, engine);
		break;
	case UIType::SETTING:
		Map::LoadUI("ViewMap/Setting", renderer, engine);
		break;
	case UIType::INSTRUMENT:
		Map::LoadUI("ViewMap/Instrument", renderer, engine);
		break;
	case UIType::LOAD_MAP:
		Map::LoadUI("ViewMap/Load", renderer, engine);
		break;
	case UIType::ADD_MAP:
		mapChoosen = Map::Create(renderer, engine);
		UIControl::GetInstance().ChangeUI(UIType::IN_GAME);
		break;
	case UIType::IN_GAME:
		if(FileExists(mapChoosen))
		{
			Map::Load(mapChoosen, renderer, engine);
			Map::LoadUI("ViewMap/InGame", renderer, engine);
		}
		else
		{
			std::cout << "Map file \"" << mapChoosen << "\" doesnt exist!" << std::endl;
		}
		break;
	}
	return true;
}

void UISystem::Update(SDL_Renderer* renderer, TTF_TextEngine* engine)
{
	
	EntityManager& em = EntityManager::GetInstance();
	for (auto& button : em.GetEntity(EntityType::BUTTON_UI))
	{
		auto& text = button->Get<Text>()->GetText();
		auto& hb = button->Get<Collider>()->GetHitBox();
		if (hb.CollideDetectPoint(mouse.GetScreenPos()))
		{
			if (mouse.GetLeftState())
			{
				
				if (text == "PlayGame" || text == "Play Game" || text == "PlayGame ")
				{
					UIControl::GetInstance().ChangeUI(UIType::PLAY_GAME);
				}
				else if (text == "Setting")
				{
					UIControl::GetInstance().ChangeUI(UIType::SETTING);
				}
				else if (text == "Instrument")
				{
					UIControl::GetInstance().ChangeUI(UIType::INSTRUMENT);
				}
				else if (text == "Load")
				{
					UIControl::GetInstance().ChangeUI(UIType::LOAD_MAP);
				}
				else if (text == "Back")
				{
					UIControl::GetInstance().BackUI();
				}
				else if (text == "Add new map")
				{
					UIControl::GetInstance().ChangeUI(UIType::ADD_MAP);
				}
				else if (UIControl::GetInstance().GetCurrentUI() == UIType::LOAD_MAP)
				{
					mapChoosen = "Map/" + text;
					UIControl::GetInstance().ChangeUI(UIType::IN_GAME);
				}
			}
		}
	}
	
	if (UIState::CHANGE == us)
	{
		us = UIState::NONE;
		UIControl& uc = UIControl::GetInstance();
		ChangeTo(uc.GetCurrentUI(), renderer, engine);
	}
	
	
	
}
