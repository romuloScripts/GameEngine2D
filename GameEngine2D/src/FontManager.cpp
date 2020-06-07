#include "FontManager.h"

TTF_Font* FontManager::LoadFont(const char* fileName, int fontSize) 
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fileName, fontSize);
	if (font == NULL)
		std::cerr << "Error initializing SDL TTF" << std::endl;
	return font;
}

void FontManager::Draw(SDL_Texture *texture, SDL_Rect position) 
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}
