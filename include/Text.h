#pragma once
#include<SDL3_ttf/SDL_ttf.h>
#include"Event.h"
#include"Component.h"

class Text : public Component
{
private:
	std::string text{};
	float font_size{};
	TTF_TextEngine* te{ nullptr };
	TTF_Font* f{ nullptr };
	TTF_Text* t{ nullptr };
public:
	constexpr static ComponentType type = ComponentType::TEXT;
	Text() = default;
	~Text() {};
	Text* SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { TTF_SetTextColor(t, r, g, b, a); return this; }
	Text* SetTextEngine(TTF_TextEngine* engine) { te = engine; return this; }
	Text* SetFont(const char* target, float size)
	{
		if (size <= 10.0f)
		{
			size = 10.0f;
		}
		if (f) TTF_CloseFont(f);
		f = TTF_OpenFont(target, size);
		font_size = size;
		return this;
	}
	Text* SetText(const std::string& text)
	{
		this->text = text;
		if (t)
		{
			TTF_DestroyText(t);
		}

		if (te && f)
			t = TTF_CreateText(te, f, this->text.c_str(), 0);
		else
			std::cout << "TextEngine or Font is not set!" << std::endl;
		SetColor(255, 0, 0, 255);
		return this;
	}

	const std::string& GetText() { return text; }
	float GetFontSize() { return font_size; }
	Text* GetTextSize(int* x, int* y) { TTF_GetTextSize(t, x, y); return this; }
	TTF_Text* GetTTFText() { return t; }
	ComponentType GetType() override { return type; }
	void Update() override {};
};
