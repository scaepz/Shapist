#ifndef DEATHMANAGER_H
#define DEATHMANAGER_H
//Crates && Items
#include "HealthBubble.h"
#include "Key.h"
#include "VectorManager.h"
#include "ItemEnum.h"

class CDeathManager
{
public:
	CDeathManager(CVectorManager * vm);
	~CDeathManager();
	void UpdateCrates();
	void UpdateAnimates();
private:
	CVectorManager* vm;
	vector<CCrate*>* crateVector;
	vector<CAnimate*>* animateVector;

};

#endif