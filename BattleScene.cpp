#include "stdafx.h"
#include "BattleScene.h"


BattleScene::BattleScene()
{
}


BattleScene::~BattleScene()
{
}

HRESULT BattleScene::init(void) 
{
	gameNode::init();

	return S_OK;
}
void BattleScene::release(void)
{
	gameNode::release();
}
void BattleScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
	}

}

void BattleScene::render(void)
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}