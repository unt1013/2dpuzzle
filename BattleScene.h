#pragma once
#include "gameNode.h"

class BattleScene : public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	BattleScene();
	~BattleScene();
};

