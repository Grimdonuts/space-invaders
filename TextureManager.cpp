#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	return IMG_LoadTexture(Game::renderer, fileName);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}