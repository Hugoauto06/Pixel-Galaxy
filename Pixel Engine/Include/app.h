#pragma once
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "defines.h"

typedef uint32_t u32;

class App
{
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_FPoint> points;
public:
	bool done, click, rightClick;
	int mouse_x, mouse_y;

	App()
	{
		u32 windowFlags = SDL_WINDOW_SHOWN;
		u32 renderFlags = SDL_RENDERER_ACCELERATED;

		window = SDL_CreateWindow(
			"Aplication",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			640, 480, windowFlags
		);
		renderer = SDL_CreateRenderer(
			window, -1, renderFlags
		);
		SDL_RenderSetScale(renderer, SCALE, SCALE);
		SDL_ShowCursor(SDL_DISABLE);

		mouse_x = 0;
		mouse_y = 0;
		done = false;
		click = false;
		rightClick = false;
	}

	void Pixel(int x, int y)
	{
		SDL_FPoint _point = { x, y };
		points.emplace_back(_point);
	}

	void ClearPixels()
	{
		points.clear();
	}

	void Shown()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (auto& p : points)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
			SDL_RenderDrawPoint(renderer, p.x, p.y);
		}

		SDL_RenderPresent(renderer);
	}

	void Inputs()
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_x, &mouse_y);
				mouse_x /= SCALE;
				mouse_y /= SCALE;
				break;
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT)
					click = false;

				if (e.button.button == SDL_BUTTON_RIGHT)
					rightClick = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
					click = true;

				if (e.button.button == SDL_BUTTON_RIGHT)
					rightClick = true;
				break;
			}
		}
	}
};