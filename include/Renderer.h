#pragma once
#include"Component.h"
#include"Texture.h"
class Renderer: public Component
{
protected:
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
	ComponentType GetType() override { return type; }
	void UpdateAttrib();
	virtual void Render();
	bool CheckEndTexture() 
	{
		if (count_row == texture->GetRow() - 1 && count_col == texture->GetCol() - 1) return true;
		else return false;
	}
	void Update() override;

};
class RendererWithAngle : public Renderer
{
protected:
	double angle{ 0.0f };
	Vec2d<float> center{};
public:
	RendererWithAngle() = default;
	~RendererWithAngle() = default;

	RendererWithAngle* SetAngle(double a) { angle = a; return this; }
	double GetAngle() const { return angle; }

	RendererWithAngle* SetCenter(const Vec2d<float>& c) { center = c; return this; }
	Vec2d<float> GetCenter() const { return center; }
	void Render() override;
	void Update() override;
};