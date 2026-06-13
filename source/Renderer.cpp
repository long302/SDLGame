#include "Renderer.h"

void Renderer::UpdateAttrib()
{
	if (renderer == nullptr || texture->GetTexture() == nullptr)
	{
		__debugbreak();
		std::cout << "Fail to render\n";
		return;
	}
	count_delay++;
	if (count_delay > delay)
	{
		count_delay = 0;
		count_col++;
	}
	if (count_col >= texture->GetCol())
	{
		count_col = 0;
		count_row++;
	}
	if (count_row >= texture->GetRow())
	{
		count_row = 0;
	}

	int w, h;
	w = texture->GetTexture()->w / texture->GetCol();
	h = texture->GetTexture()->h / texture->GetRow();
	src = { (float)(count_col)*w,(float)(count_row)*h, (float)w, (float)h };
}

void Renderer::Render()
{
	SDL_RenderTexture(renderer, texture->GetTexture(), &src, &dst);
}

void Renderer::Update()
{
	UpdateAttrib();
	Render();	
}

void RendererWithAngle::Update()
{
	UpdateAttrib();
	Render();
}
void RendererWithAngle::Render()
{
	SDL_FPoint sdl_center = { center.x, center.y };
	SDL_RenderTextureRotated(renderer, texture->GetTexture(), &src, &dst, angle, &sdl_center, SDL_FLIP_NONE);
}

void TextRenderer::Render()
{
	SDL_RenderTexture(renderer, texture->GetTexture(), &src, &dst);
	TTF_DrawRendererText(text, text_pos.x, text_pos.y);
}
void TextRenderer::Update()
{
	UpdateAttrib();
	Render();
}
