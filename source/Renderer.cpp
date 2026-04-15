#include "Renderer.h"

void Renderer::Update()
{
	if (renderer == nullptr || texture == nullptr)
	{
		std::cout << "Fail to render";
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
	
	
	//std::cout << count_row << " " << count_col << " " << count_delay << std::endl;
	
	int w, h;
	w = texture->GetTexture()->w / texture->GetCol();
	h = texture->GetTexture()->h / texture->GetRow();
	src = { (float)(count_col ) * w,(float)(count_row )* h, (float)w, (float)h };
	SDL_RenderTexture( renderer, texture->GetTexture(),&src,&dst);
}
