#include "AI.h"


CAI::CAI(CVectorManager* _vm)
{
	vm = _vm;
	tileVector = vm->GetTileVector();
	player = vm->GetPlayer();
}


CAI::~CAI()
{
}


bool CAI::IsPlayerInLineOfSight(int maxDistance, CEnemy * self)	
{
	//pythagoras to check if within maxdistance
	if (sqrt((player->GetX() - self->GetX()) * (player->GetX() - self->GetX()) + (player->GetY() - self->GetY()) * (player->GetY() - self->GetY())) < maxDistance)
	{
		 
		//check if there are any tiles between player and enemy (from enemy eye-height (height/4) to player top and bottom)

		//first rule out tiles not between player and enemy
		int minX, maxX;
		int minY, maxY;
		if (self->GetX() > player->GetX())
		{
			minX = player->GetX() / vm->standardTileSize;
			maxX = self->GetX() / vm->standardTileSize;
		}
		else
		{
			minX = self->GetX() / vm->standardTileSize;
			maxX = player->GetX() / vm->standardTileSize;
		}
		if (self->GetY() > player->GetY())
		{
			minY = (player->GetY() ) / vm->standardTileSize;
			maxY = self->GetY() / vm->standardTileSize;
		}
		else
		{
			minY = (self->GetY() ) / vm->standardTileSize;
			maxY = player->GetY() / vm->standardTileSize;
		}
		
		//points to check
		int x1, x2, y1, y2;
		x1 = self->GetX();
		y1 = self->GetY();
		
		//loop through remaining tiles.
		//to optimize i could use an equation to find position in matrix of next tile
		for (int x = minX; x <= maxX; x++)
		{
			for (int y = minY; y <= maxY; y++)
			{
				if (tileVector->at(y).at(x) != nullptr)
				{
					SDL_Rect rect;
					rect.x = x* vm->standardTileSize;
					rect.y = y* vm->standardTileSize;
					rect.w = vm->standardTileSize;
					rect.h = rect.w;

					x2 = player->GetX(); 
					y2 = player->GetY();

					if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2))
					{
						return false;						
					}
				}
			}
		}
		return true; //return true if loop ends without returning false
	}
	else return false;

}

int CAI::GetIncrementalInt()
{
	incrementalIntForRandomizer++;
	return incrementalIntForRandomizer;
}

void CAI::GetEnemyCrosshairPlacement(float * previousRotation, float *previousRotationVelocity, int optimalRotation) 
{
	g_time = 10;
	if (*previousRotation >= 270) *previousRotation = 269.9f;
	if (*previousRotation <= -90) *previousRotation = -89.9f;
	//-90 -> 270 clockwise from 12
	float difference = optimalRotation - *previousRotation;
	if (previousRotationVelocity == 0)
	{
		if (difference > 0)
		{
			*previousRotationVelocity = 0.001f;
		}
		else if (difference < 0)
		{
			*previousRotationVelocity = -0.001f;
		}
		else return;
	}
	else
	{
		if ((*previousRotationVelocity > 0 && difference < 0) || previousRotationVelocity < 0 && difference > 0) //If xhair going wrong way
		{
			if (*previousRotationVelocity < 0.001f)	//if xhair is going very slow -> switch direction
			{
				*previousRotationVelocity *= -1;
			}
			else
			{
				for (int i = 0; i < g_time; i++)	//else slow down
				{
					*previousRotationVelocity *= 0.95f;
				}
			}
		}
		else //if xhair is going right way speed up proportional to difference
		{
			*previousRotationVelocity += g_time* (difference / 30000);
		}
	}

	*previousRotation += *previousRotationVelocity * g_time;
}