#ifndef WEAPON_H
#define WEAPON_H
#include "sdl.h"
#include "WeaponsEnum.h"
#include <vector>
#include <string>
class CWeapon
{
public:
	CWeapon();
	virtual ~CWeapon();
	virtual bool Attack(int x, int y, float dirX, float dirY) = 0;
	virtual void CeaseFire();
	virtual void Update();

	virtual int GetFrame();

	int fireSound = -1;

	int kickBackX = 1;
	int kickBackY = 1;
	int kickBackRot = 1;
	int kickBackTime = 1;
	std::string name ="empty";
	int width = 12;
	int height = 12;
	int offsetX= 0;
	int offsetY =0;
	int textureId = 404;
	int iconId = 404;
	SDL_Point flipPoint;
	int reloadDelay = 200;
	int clipSize = 4;
	int switchDelay = 200;
	int fireDelay = 100;
	int ammoType = rifleAmmo;
	int ammoCost = 1;
	int GetFrameSizeX();
	int GetFrameSizeY();
protected:
	int frameSizeX = 0;
	int frameSizeY = 0;
};

#endif