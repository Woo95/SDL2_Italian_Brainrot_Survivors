#include "Enemy.h"

class CStalker : public CEnemy
{
public:
	CStalker();
	virtual ~CStalker();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};