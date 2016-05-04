#pragma once

#include <SDL.h>
#include <SDL_image.h>

namespace sdltest {

class SampleSurface {
public:
	SampleSurface(SDL_Window* pWindow);
	~SampleSurface();

	bool init();
	bool load();
	void update(int x, int y);
	void clear();

private:
	SDL_Window* pWindow;
	SDL_Surface* pWindowSurface;
	SDL_Surface* pImageSurface;
};

}
