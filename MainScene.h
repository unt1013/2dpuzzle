#pragma once
#include "gameNode.h"

class MainScene : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainScene();
	~MainScene();
};

