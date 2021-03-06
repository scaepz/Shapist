#ifndef ENEMY_H
#define ENEMY_H
#include "Animate.h"


class CEnemy :
	public CAnimate
{
public:
	CEnemy(int x, int y, int textureId, int size, vector<CWeapon*> & weaponVector);
	virtual ~CEnemy();
	int GetFrame();
	void OnCollision(bool, bool);
	void SetRotation(float _rotation);
	//ai stuff
	int reactionTime;
	int timeUntilReaction;
	int rangeOfVision;

	int AI = 0;
	int aiParam[4];

	bool GetPlayerVisible();
	bool GetPlayerVisibleStale();
	void SetPlayerVisible(bool);
	void UpdateTime(int time);
	void ResetTimeUntilReaction();
	void UpdateTimeUntilReaction(int time);
	int GetTimeUntilReaction();
	bool IsAwareOfPlayer(); 
	float crosshairVelocity;
private:	
	int timeSincePlayerNotVisible;
	bool playerVisible;
	int timeSincePlayerVisibilityCheck;

};

#endif