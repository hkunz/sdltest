#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

namespace sdltest {

class SampleRenderer {
public:
	SampleRenderer(SDL_Window* pWindow);
	~SampleRenderer();

	bool init();
	bool load();
	void update(int x = 0, int y = 0);

private:
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
	SDL_Texture* pTexture;
	unsigned int width;
	unsigned int height;
};
}
