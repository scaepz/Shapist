#pragma once
class IDamagable
{
public:
	IDamagable();
	virtual void TakeDamage(int amount) = 0;
	virtual ~IDamagable();
};

