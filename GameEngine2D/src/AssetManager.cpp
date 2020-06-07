#include "AssetManager.h"

AssetManager::AssetManager(EntityManager * manager)
{

}

AssetManager::~AssetManager()
{
}

void AssetManager::ClearData()
{
	textures.clear();
}

void AssetManager::AddTexture(std::string textureid, const char * filepath)
{
	textures.emplace(textureid, TextureManager::LoadTexture(filepath));
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) 
{
	fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

SDL_Texture * AssetManager::GetTexture(std::string textureId)
{
	return textures[textureId];
}

TTF_Font* AssetManager::GetFont(std::string fontId) 
{
	return fonts[fontId];
}
