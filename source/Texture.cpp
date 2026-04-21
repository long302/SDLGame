#include"Texture.h"


bool Texture::Load(SDL_Renderer* renderer, const char* path)
{
	SDL_DestroyTexture(tex);
	tex = nullptr;
	tex = IMG_LoadTexture(renderer, path);
	if (!tex)
	{
		std::cout << "Load Texture: " << path << " Fail\n";
		return false;
	}
	return true;
}
bool TextureManager::AddTexture(EntityType e_type, TextureType t_type, SDL_Renderer* renderer, const char* path, int row, int col)
{
	textures[e_type][t_type].Load(renderer, path);
	textures[e_type][t_type].SetRowCol(row, col);
	return true;
}
bool TextureManager::AddTexture(EntityType e_type, TextureType t_type, SDL_Renderer* renderer, const std::string& path, int row, int col)
{
	textures[e_type][t_type].Load(renderer, path.c_str());
	textures[e_type][t_type].SetRowCol(row, col);
	return true;
}

TextureManager* TextureManager::DestroyTexture(EntityType e_type)
{
	for (auto& m : textures[e_type])
	{
		m.second.Destroy();
	}
	textures[e_type].clear();
	return this;
}

void Imager::Update()
{
}
