#pragma once
#include"Event.h"
#include"Component.h"
enum class TextureType
{
	NONE,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP,
	FALL,
	USING_SKILL_1,

};
constexpr std::string_view GetStringOf(TextureType type)noexcept
{
	switch (type)
	{
	case TextureType::NONE:   return "TextureType::NONE";
	case TextureType::RUN_LEFT: return "TextureType::RUN_LEFT";
	case TextureType::RUN_RIGHT:  return "TextureType::RUN_RIGHT";
	case TextureType::JUMP: return "TextureType::JUMP";
	case TextureType::FALL: return "TextureType::FALL";
	default: return "Unknown";
	}	
}

class TextureManager;
class Texture
{
private:
	SDL_Texture* tex{ nullptr };
	int row{}, col{};
public:
	Texture() {}
	~Texture() {}
	
	Texture* SetRowCol(int row, int col) { this->row = row, this->col = col; return this; }
	bool Load(SDL_Renderer* renderer, const char* path);
	SDL_Texture* GetTexture() const { return tex; }
	int GetRow() { return row; }
	int GetCol() { return col; }
	Texture* Destroy() { SDL_DestroyTexture(tex); return this; }

	friend TextureManager;
};
class TextureManager
{
private:
	std::map<EntityType, std::map<TextureType,Texture>> textures;
	TextureManager() {};
public:
	~TextureManager() {};
	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
	bool AddTexture(EntityType e_type,TextureType t_type,SDL_Renderer* renderer, const char* path, int row, int col);
	Texture& GetTexture(EntityType e_type, TextureType tex_type)  
	{
		if (textures.find(e_type) == textures.end())
		{
			std::cout << GetStringOf(e_type) << " doesnt have " << GetStringOf(tex_type) << std::endl;
			__debugbreak();
		}
		return textures[e_type][tex_type];
	}
	TextureManager* DestroyTexture(EntityType e_type);
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
};
class Imager: public Component
{
private:
	TextureType tex_type{};
	Texture* texture{nullptr};
public:
	static constexpr ComponentType type = ComponentType::IMAGE;

	Imager() {};
	~Imager() {};
	Imager* SetTextureType(TextureType t) { tex_type = t; return this; }
	Imager* SetTexture(Texture* tex) { texture = tex; return this; }
	Texture* GetTexture() { return texture;}
	TextureType GetTextureType() { return tex_type; }

	void Update() override;
};