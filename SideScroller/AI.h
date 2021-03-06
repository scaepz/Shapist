#ifndef AI_H
#define AI_H
#include <vector>
#include "Commands.h"
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"
#include "Global.h"
#include "VectorManager.h"
#include "SDL.h"

using std::vector;
class CAI
{
public:
	CAI(CVectorManager * _vm);
	virtual ~CAI();
	virtual void MakeDecision(CEnemy* self) = 0;
	bool IsPlayerInLineOfSight(int maxDistance, CEnemy * self);//expensive operation, only call once in a while
	int GetIncrementalInt();
	/* GetEnemyCrosshairPlacement
	do not call every frame, call only based on time
	x,y: give the previous x and y direction variables, get the new ones
	xvel yvel: give the previous x and y velocity variables, get the new ones (just for storing them for this function)
	optimalx, optimaly: enemypos - playerpos (perfect direction variables)
	*/
	void GetEnemyCrosshairPlacement(float * previousRotation, float *previousRotationVelocity, int optimalRotation);
protected:
	int incrementalIntForRandomizer= 0;
	CVectorManager *vm;
	CPlayer * player;
	vector<vector<CTile*>>* tileVector;
	

};

#endif