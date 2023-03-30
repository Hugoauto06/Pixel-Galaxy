#include <iostream>
#include "app.h"
#include "frameRate.h"
#include "physicsObject.h"
#include "defines.h"

void createPhysics(std::vector<physicsObject*>* physicsObjs, int x, int y)
{
	bool canSpawn = true;
	for (int i = 0; i < physicsObjs->size(); i++)
	{
		if (x == physicsObjs->at(i)->x && y == physicsObjs->at(i)->y)
		{
			canSpawn = false;
			break;
		}
	}
	if (canSpawn)
	{
		physicsObject* _p = new physicsObject(x, y);
		physicsObjs->emplace_back(_p);
	}
}

void ErasePhysics(std::vector<physicsObject*>* physicsObjs, int x, int y)
{
	for (int i = 0; i < physicsObjs->size(); i++)
	{
		if (x == physicsObjs->at(i)->x && y == physicsObjs->at(i)->y)
		{
			physicsObjs->erase(physicsObjs->begin()+i);
			break;
		}
	}
}

int main(int argc, char** args)
{
	std::vector<physicsObject*> physicsObjs;
	App app;
	long then;
	float remainder;
	short clickDelay = 0;
	remainder = 0;
	
	then = SDL_GetTicks();
	while (!app.done)
	{
		clickDelay++;
		app.Inputs();
		for (int i = 0; i < physicsObjs.size(); i++)
		{
			physicsObjs[i]->Update(&physicsObjs);
		}
		if (app.click /*&& clickDelay >= 50*/)
		{
			createPhysics(&physicsObjs, app.mouse_x, app.mouse_y);
			//clickDelay = 0;
		}

		if (app.rightClick)
		{
			ErasePhysics(&physicsObjs, app.mouse_x, app.mouse_y);
		}
		

		app.ClearPixels();
		for (int i = 0; i < physicsObjs.size(); i++)
		{
			app.Pixel(physicsObjs[i]->x, physicsObjs[i]->y);
		}

		/* */
		app.Pixel(app.mouse_x, app.mouse_y);

		app.Shown();
		
		CapFrameRate(&then, &remainder);
	}

	for (int i = 0; i < physicsObjs.size(); i++)
	{
		free(physicsObjs[i]);
	}

	return 0;
}