#include "test/SampleSurface.h"
#include "stdio.h"
#include "stddef.h"

namespace sdltest {

SampleSurface::SampleSurface(SDL_Window* pWindow) :
		pWindow(pWindow), pWindowSurface(nullptr), pImageSurface(nullptr) {
}

SampleSurface::~SampleSurface() {
	SDL_FreeSurface(pImageSurface);
	pImageSurface = nullptr;
}

bool SampleSurface::init() {
	pWindowSurface = SDL_GetWindowSurface(pWindow);
	return true;
}

bool SampleSurface::load() {
	if (!pWindowSurface) {
		return false;
	}
	const char* imagePath = "images/akiko.bmp";
	SDL_Surface* temp = pImageSurface = IMG_Load(imagePath);
	if (pImageSurface == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", imagePath,
				SDL_GetError());
		return false;
	}
	pImageSurface = SDL_ConvertSurface(pImageSurface, pWindowSurface->format,
			0);
	SDL_FreeSurface(temp);
	return true;
}

void SampleSurface::update(int x, int y) {
	if (!pWindowSurface) {
		return;
	}
	clear();
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(pImageSurface, nullptr, pWindowSurface, &rect);
	SDL_UpdateWindowSurface(pWindow);
}

void SampleSurface::clear() {
	SDL_FillRect(pWindowSurface, nullptr,
			SDL_MapRGB(pWindowSurface->format, 0xFF, 0x00, 0x00));
}

}
