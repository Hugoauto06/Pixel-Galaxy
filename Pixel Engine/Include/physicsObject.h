#pragma once
#include "object.h"

class physicsObject
{
public:
	int x, y;
	physicsObject(int X, int Y)
	{
		x = X;
		y = Y;
	}
	void Update(std::vector<physicsObject*>* physicsObjs)
	{
		bool canGoDown = true;
		for (size_t i = 0; i < physicsObjs->size(); i++)
		{
			if (y < SCREEN_HEIGHT - 1)
			{
				if (y + 1 == physicsObjs->at(i)->y && x == physicsObjs->at(i)->x)
				{
					canGoDown = false;
				}
			}
			else
			{
				canGoDown = false;
			}
		}

		if (canGoDown)
			y++;
	}
};