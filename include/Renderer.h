#pragma once
#include"Component.h"
#include"Texture.h"
class Renderer: public Component
{
private:
	SDL_Renderer* renderer{ nullptr };
	Texture* texture{ nullptr };
	SDL_FRect src{NULL};
	SDL_FRect dst{NULL};

	int delay{};

	int count_row{0};
	int count_col{0};
	int count_delay{0};
	  
public:
	constexpr static ComponentType type = ComponentType::RENDER;

	Renderer() = default;
	~Renderer() = default;

	Renderer* SetRenderer(SDL_Renderer* r) { renderer = r; return this; }
	Renderer* SetTexture(Texture* t) 
	{
		texture = t;
		return this; 
	}
	Renderer* SetSrcRect(const SDL_FRect& rect) { src = rect; return this; }
	Renderer* SetDstRect(const SDL_FRect& rect) { dst = rect; return this; }
	Renderer* SetDelay(int delay) { this->delay = delay; return this; }

	SDL_Renderer* GetRenderer() { return renderer; }
	void Update() override;
};