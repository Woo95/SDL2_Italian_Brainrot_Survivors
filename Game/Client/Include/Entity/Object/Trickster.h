#include "Enemy.h"

class CTrickster : public CEnemy
{
public:
	CTrickster();
	virtual ~CTrickster();

public:
	virtual bool Init() final;

private:
	virtual void Release() final;
};