#pragma once
#include"GameSystem.h"
#include<fstream>
namespace Map
{
	void Create(SDL_Renderer* renderer);
	void Save(const std::string& file_name);
	void Load(const std::string& file_name,SDL_Renderer* renderer);
}
