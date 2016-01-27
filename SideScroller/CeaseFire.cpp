#include "CeaseFire.h"
#include "Weapon.h"

CCeaseFire::CCeaseFire(CAnimate * obj) : CCommandObject(obj)
{
	commandId = ceaseFire;
}


CCeaseFire::~CCeaseFire()
{
}

bool CCeaseFire::Execute()
{
	obj->weaponVector->at(obj->GetWeaponEquipped())->CeaseFire();
	return true;
}