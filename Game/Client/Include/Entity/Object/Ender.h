#include "Enemy.h"

class CEnder : public CEnemy
{
public:
	CEnder();
	virtual ~CEnder();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};