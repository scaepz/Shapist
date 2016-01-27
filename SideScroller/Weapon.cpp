#include "Weapon.h"


CWeapon::CWeapon()
{
	flipPoint.x = 0;
	flipPoint.y = 0;
}


CWeapon::~CWeapon()
{

}

void CWeapon::CeaseFire()
{
	return;
}

void CWeapon::Update()
{
	
}
int CWeapon::GetFrame()
{
	return 0;
}
int CWeapon::GetFrameSizeX()
{
	return frameSizeX;
}
int CWeapon::GetFrameSizeY()
{
	return frameSizeY;
}