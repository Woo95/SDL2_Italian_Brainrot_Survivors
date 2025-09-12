#include "Enemy.h"

class CMaddener : public CEnemy
{
public:
	CMaddener();
	virtual ~CMaddener();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};