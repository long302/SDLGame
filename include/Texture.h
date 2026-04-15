#pragma once
#include"Event.h"
#include"Component.h"
enum class TextureType
{
	NONE
};
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
	Texture& GetTexture(EntityType e_type, TextureType tex_type)  { return textures[e_type][tex_type]; }
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