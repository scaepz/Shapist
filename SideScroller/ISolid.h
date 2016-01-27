#ifndef ISOLID_H
#define ISOLID_H
class ISolid
{
public:
	ISolid();
	virtual	~ISolid();
	virtual void TakeDamage(int amount) = 0;
	virtual int GetX() = 0;
	virtual int GetY() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
};
#endif
