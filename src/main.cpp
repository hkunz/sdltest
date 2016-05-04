#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "common/Version.h"
#include "common/globals.h"
#include "test/SampleSurface.h"
#include "test/SampleRenderer.h"

using namespace sdltest;

SDL_Window* pWindow = nullptr;

bool init();
void close();

int main(int/*argc*/, char**/*argv[]*/) {
	if (!init()) {
		return EXIT_FAILURE;
	}

	const int inc = 10;
	int x = 0;
	int y = 0;
	bool invalidate = false;

	SampleSurface sampleSurface(pWindow);
	//sampleSurface.init();
	sampleSurface.load();
	sampleSurface.update(x, y);

	SampleRenderer sampleRenderer(pWindow);
	sampleRenderer.init();
	sampleRenderer.load();
	sampleRenderer.update();


	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					printf("up\n");
					y -= inc;
					break;
				case SDLK_DOWN:
					printf("down\n");
					y += inc;
					break;
				case SDLK_LEFT:
					printf("left\n");
					x -= inc;
					break;
				case SDLK_RIGHT:
					printf("right\n");
					x += inc;
					break;
				default:
					break;
				}
				invalidate = true;
				printf("value %dx%d\n", x, y);
			}
			if (invalidate) {
				invalidate = false;
				sampleSurface.update(x, y);
				sampleRenderer.update(x, y);
			}
		}
	}
	close();
	return EXIT_SUCCESS;
}

bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, SDL_WINDOW_SHOWN); //SDL_WINDOW_FULLSCREEN_DESKTOP
	if (pWindow == nullptr) {
		printf("pWindow could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	return true;
}

void close() {
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	IMG_Quit();
}
