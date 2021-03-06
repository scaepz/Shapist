#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "Weapon.h"
#include "VectorManager.h"
class CMeleeWeapon :
	public CWeapon
{
public:
	CMeleeWeapon(CVectorManager * vm);
	virtual ~CMeleeWeapon();
	bool Attack(int x, int y, float dirX, float dirY);
	int GetFrame();
	int maxLength;
	int staminaCost;
	int damage;
	void Update();
	int timeSinceAnimationStart;
	enum animationDataType
	{
		frameCountData,
		msPerFrameData,
		startFrameData,
		numberOfDataTypes
	};
	enum animations
	{
		idle,
		attack1,
		attack2,
		numberOfAnimations
	};
	int animationData[numberOfAnimations][numberOfDataTypes];
private:

	
	int currentAnimation;
	void StartAnimation(int);

	CVectorManager * vm;

};

#endif