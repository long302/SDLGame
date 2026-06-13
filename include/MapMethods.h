#pragma once
#include"GameSystem.h"
#include<filesystem>
#include<fstream>
static bool FileExists(const std::string& path)
{
	return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}
static std::vector<std::string> getFileNames(const std::string& folderPath) {
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }

    return files;
}
namespace Map
{
	std::string Create(SDL_Renderer* renderer, TTF_TextEngine* te);
	void Save(const std::string& file_name);
	void Load(const std::string& file_name,SDL_Renderer* renderer, TTF_TextEngine* te);
	void LoadUI(const std::string& file_name, SDL_Renderer* renderer, TTF_TextEngine* te);
	void Update(SDL_Renderer* renderer, TTF_TextEngine* te);
}
