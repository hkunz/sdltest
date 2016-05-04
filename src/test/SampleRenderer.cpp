#include "test/SampleRenderer.h"
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <string>

namespace sdltest {

SampleRenderer::SampleRenderer(SDL_Window* pWindow) :
		pWindow(pWindow), pRenderer(nullptr), pTexture(nullptr), width(0), height(0) {
}

SampleRenderer::~SampleRenderer() {
	SDL_DestroyTexture(pTexture);
	pTexture = nullptr;
	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;
}

bool SampleRenderer::init() {
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (pRenderer == nullptr) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	return true;
}

bool SampleRenderer::load() {
	if (pRenderer == nullptr) {
		return false;
	}
	std::string path = "images/akiko.bmp";
	const char* image = path.c_str();
	SDL_Surface* loadedSurface = IMG_Load(image);
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", image,
		IMG_GetError());
		return false;
	}
	pTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
	if (pTexture == nullptr) {
		printf("Unable to create texture from %s! SDL Error: %s\n", image, SDL_GetError());
		return false;
	}
	SDL_FreeSurface(loadedSurface);
	return true;
}

void SampleRenderer::update(int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 275;
	rect.h = 275;
	SDL_RenderClear(pRenderer);
	SDL_RenderCopy(pRenderer, pTexture, nullptr, &rect);
	SDL_RenderPresent(pRenderer);
}

}
