#include "stdafx.h"
#include "GameObject.h"
#include "player.h"
#include "Wall.h"
#include "Boom.h"
#include "Npc.h"
#include "Shrine.h"
#include "traps.h"
#include "container.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

HRESULT GameObject::init(string MapKey, string BgmKey, string ShopkeeperKey, int bpm)
{
	Load(MapKey);
	EFFECTMANAGER->addEffect("fire", "fire", 336, 48, 48, 48, 1, TIMEMANAGER->getElapsedTime() * 10, 200);
	EFFECTMANAGER->addEffect("BossAttack", "BossAttack", 270, 48, 54, 48, 1, TIMEMANAGER->getElapsedTime() * 20, 200);
	EFFECTMANAGER->addEffect("폭발", "폭발", 720, 144, 144, 144, 1, TIMEMANAGER->getElapsedTime() * 10, 200);
	EFFECTMANAGER->addEffect("폭발어둠", "폭발어둠", 720, 144, 144, 144, 1, TIMEMANAGER->getElapsedTime() * 10, 200);
	Sys = new RhythmSystem;
	Sys->init();
	Sys->registStageMusic(0, BgmKey, ShopkeeperKey, bpm);
	Sys->startStageMusic(0);
	Sys->changeTempo(1.0);

	_itemFactory = new ItemFactory;

	
	//에이스타 관련 변수 초기화
	_count = 0;
	_start = true;
	_dNum = 0;

	_sightPower = 8;
	_torchPower = 5;

	Sys2 = new SightSystem;
	Sys2->init(_TileNum, &_vTileMap, _sightPower, _torchPower);
	setAlpha(255);

	_keybuffer = tagKeyBuffer(false);
	_turnActive = false;

	return S_OK;
}

void GameObject::release()
{
	RELEASE_DELETE(_player);
	RELEASE_DELETE(Sys);
	RELEASE_DELETE(Sys2);
	RELEASE_DELETE(_itemFactory);

	for (int i = 0; _vTileMap.size() > 0;)
	{
		RELEASE_DELETE(_vTileMap[i]);
		_vTileMap.erase(_vTileMap.begin());
	}
	for (int i = 0; _vItem.size() > 0;)
	{
		RELEASE_DELETE(_vItem[i]);
		_vItem.erase(_vItem.begin());
	}
	for (int i = 0; _vMonster.size() > 0;)
	{
		RELEASE_DELETE(_vMonster[i]);
		_vMonster.erase(_vMonster.begin());
	}
	for (int i = 0; _vMonster.size() > 0;)
	{
		RELEASE_DELETE(_vWall[i]);
		_vWall.erase(_vWall.begin());
	}
	for (int i = 0; _vBoom.size() > 0;)
	{
		RELEASE_DELETE(_vBoom[i]);
		_vBoom.erase(_vBoom.begin());
	}
	for (int i = 0; _vCon.size() > 0;)
	{
		RELEASE_DELETE(_vCon[i]);
		_vCon.erase(_vCon.begin());
	}
	for (int i = 0; _vTrap.size() > 0;)
	{
		RELEASE_DELETE(_vTrap[i]);
		_vTrap.erase(_vTrap.begin());
	}
	for (int i = 0; _vShrine.size() > 0;)
	{
		RELEASE_DELETE(_vShrine[i]);
		_vShrine.erase(_vShrine.begin());
	}
	for (int i = 0; _vNpc.size() > 0;)
	{
		RELEASE_DELETE(_vNpc[i]);
		_vNpc.erase(_vNpc.begin());
	}
	
	_vTileMap.clear();
}

void GameObject::update()
{

	updateKeyBuffer();
	setTorchLightPower();
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
	}

	for (int i = 0; i < _vMonster.size(); i++)
	{
		_vMonster[i]->update();
	}
	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i]->update();
	}
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->update();
	}
	for (int i = 0; i < _vWall.size(); i++)
	{
		_vWall[i]->update();
	}
	Sys->update();

	if (Sys->getJudgement() == JUDGEMENT::GOOD ||
		Sys->getJudgement() == JUDGEMENT::PERPECT)
	{
		_keybuffer.isActive = true;
	}

	else if (Sys->getJudgement() == JUDGEMENT::MISS)
	{
		for (int i = 0; i < _vBoom.size(); i++)
		{
			_vBoom[i]->setBoomframeX(1);
		}
		for (int i = 0; i < _vMonster.size(); i++)
		{
			_vMonster[i]->monsterAI();
		}
		for (int i = 0; i < _vTileMap.size(); i++)
		{
			_vTileMap[i]->update();
		}
		for (int i = 0; i < _vShrine.size(); i++)
		{
			_vShrine[i]->update();
		}
	}
	if (Sys->getJudgement() == JUDGEMENT::FAIL ||
		Sys->getJudgement() == JUDGEMENT::MISS)
	{
		GLOBALDATA->setBunGuck(1);
		GLOBALDATA->setComboCount(0);
	}

	if (_turnActive)
	{
		bool canMove = true;
		_keybuffer.isActive = false;
		if (_keybuffer.down && _keybuffer.left)
		{
			MakeBoom(_player->getPlayerTileIndex().x, _player->getPlayerTileIndex().y);
			canMove = false;
		}
		else if (_keybuffer.up && _keybuffer.left)
		{
			canMove = !_player->consume(0, this);
		}
		else if (_keybuffer.up && _keybuffer.right)
		{
			canMove = !_player->consume(1, this);
		}
		else if (_keybuffer.up)
		{
			canMove = _player->attack(DIRECTION_4::TOP, this);
			if (canMove)_player->keyControl(DIRECTION_4::TOP);
		}
		else if (_keybuffer.down)
		{
			canMove = _player->attack(DIRECTION_4::BOTTOM, this);
			if (canMove)_player->keyControl(DIRECTION_4::BOTTOM);
		}
		else if (_keybuffer.left)
		{
			canMove = _player->attack(DIRECTION_4::LEFT, this);
			if (canMove)_player->keyControl(DIRECTION_4::LEFT);
		}
		else if (_keybuffer.right)
		{
			canMove = _player->attack(DIRECTION_4::RIGHT, this);
			if (canMove)_player->keyControl(DIRECTION_4::RIGHT);
		}

		_player->update();
		for (int i = 0; i < _vBoom.size(); i++)
		{
			_vBoom[i]->setBoomframeX(1);
		}
		for (int i = 0; i < _vMonster.size(); i++)
		{
			_vMonster[i]->monsterAI();
		}
		for (int i = 0; i < _vTileMap.size(); i++)
		{
			_vTileMap[i]->update();
		}
		for (int i = 0; i < _vShrine.size(); i++)
		{
			_vShrine[i]->update();
		}
		_turnActive = false;
	}
	else
	{
		_player->update();
	}

	BoomUpdate();
	if (_vNpc.size() != 0) setVolume();
	if (_vNpc.size() == 0) Sys->shopMusicVolumeSetting(0);
	Sys2->update(_player->getPlayerTileIndex().x, _player->getPlayerTileIndex().y, _sightPower, _torchPower);

	_camera.setCamera(fRectMakeCenter(_player->getPosition().x, _player->getPosition().y, WINSIZEX, WINSIZEY));

	MonsterHunt();
	EFFECTMANAGER->update();
	distructContainer();
}

void GameObject::render()
{
	for (int i = 0; i < _vTileMap.size(); i++)
	{
		_vTileMap[i]->render(48, 48, _camera.getLeft(), _camera.getTop());
	}
	for (int i = 0; i < _vTrap.size(); i++)
	{
		_vTrap[i]->render(_camera.getLeft(), _camera.getTop());
	}
	for (int i = 0; i < _vTileMap.size(); i++)
	{
		_vTileMap[i]->goldRender(48, 48, _camera.getLeft(), _camera.getTop());
	}
	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i]->render(_camera.getLeft(), _camera.getTop());
	}
	for (int i = 0; i < _vTileMap.size(); i++)
	{
		if (_vTileMap[i]->getWall() != NULL)
		{
			_vTileMap[i]->getWall()->render(_camera.getLeft(), _camera.getTop());
		}
		_vTileMap[i]->getBlack()->frameAlphaRender(getMemDC(),
			(i % _TileNum.x) * GLOBALDATA->getIndexSizeWidth() -_camera.getLeft(),
			(i / _TileNum.x)* GLOBALDATA->getIndexSizeHeight() + 48 - _vTileMap[i]->getBlack()->getFrameHeight() - _camera.getTop(),
			0, 0, _vTileMap[i]->getAlpha());
		if (_vTileMap[i]->getShrine() != NULL)
		{
			_vTileMap[i]->getShrine()->render(_camera.getLeft(), _camera.getTop());
		}
		if (_vTileMap[i]->getcontainer() != NULL)
		{
			_vTileMap[i]->getcontainer()->render(_camera.getLeft(), _camera.getTop(), _player->getMonocleBool());
		}
		if (_vTileMap[i]->getItem() != NULL)
		{
			_vTileMap[i]->getItem()->render(_camera.getLeft(), _camera.getTop());
		}
		if (_vTileMap[i]->getNpc() != NULL)
		{
			_vTileMap[i]->getNpc()->render(_camera.getLeft(), _camera.getTop());
		}
		if (_vTileMap[i]->getPlayer() != NULL)
		{
			_vTileMap[i]->getPlayer()->render(_camera.getLeft(), _camera.getTop());
		}
		if (_vTileMap[i]->getMonster() != NULL)
		{
			_vTileMap[i]->getMonster()->render(_camera.getLeft(), _camera.getTop());
		}
	}
	
	Sys->render();

	EFFECTMANAGER->render(_camera.getLeft(), _camera.getTop());
}

void GameObject::Load(string MapKey)
{
	MAP_TOOL::MapToolTileMap Temp;
	Temp.load(MapKey); 
	
	int idx = 0;
	int idy = 0;

	_TileSize = PointMake(Temp.tileSizeX, Temp.tileSizeY);
	_TileNum = PointMake(Temp.tileMapWidth, Temp.tileMapHeight);

	for (int i = 0; i < _TileNum.y; i++)
	{
		for (int j = 0; j < _TileNum.x; j++)
		{
			int index = i*_TileNum.x + j;
			GameTile* _Tile;
			_Tile = new GameTile;
			_Tile->init(Temp.tileMap[index].ground, j, i);
			_vTileMap.push_back(_Tile);
			if (Temp.tileMap[index].monster != MAP_TOOL::MONSTER::NONE)
			{
				MakeMonster(Temp.tileMap[index].monster, j, i, (THETA_UTIL::DIRECTION_4)RND->getInt(4));
			}//몬스터
			if (Temp.tileMap[index].npc != MAP_TOOL::NPC::NONE)
			{
				idx = j;
				idy = i;
			}//엔피씨
			if (Temp.tileMap[index].container != MAP_TOOL::CONTAINER::NONE)
			{
				MakeContainer(Temp.tileMap[index].container, j, i);
			}//콘테이너
			if (Temp.tileMap[index].item.type != MAP_TOOL::ITEM::TYPE::NONE)
			{
				MakeItem(j, i, Temp.tileMap[index].item);
			}//아이템
			if (Temp.tileMap[index].shrine != MAP_TOOL::SHRINE::NONE)
			{
				MakeShrine(Temp.tileMap[index].shrine, j, i);
			}//제단
			if (Temp.tileMap[index].wall != MAP_TOOL::WALL::NONE)
			{
				bool A;
				if (Temp.tileMap[index].torch == MAP_TOOL::TORCH::NONE) A = false;
				else A = true;
				MakeWall(Temp.tileMap[index].wall, j, i, A);
			}//벽
			if (Temp.tileMap[index].trap != MAP_TOOL::TRAP::NONE)
			{
				MakeTrap(Temp.tileMap[index].trap, j, i);
			}//함정
			if (Temp.tileMap[index].gold != 0)
			{
				_Tile->addGold(Temp.tileMap[index].gold);
			}
			
		}
	}

	if (idx != 0 && idx != 0)
	{
		MakeNPC(Temp.tileMap[idx + idy * _TileNum.x].npc, idx, idy);
		_vTileMap[idx - 2]->setShopTile();
		_vTileMap[idx + 2]->setShopTile();
	}
	
	_player = new player;
	_player->init(this);
	_player->placePlayer(Temp.playerIndexList[0].x, Temp.playerIndexList[0].y);
	_vTileMap[Temp.playerIndexList[0].x + _TileNum.x * Temp.playerIndexList[0].y]->setObject(_player);
}

void GameObject::PlayerMove(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _player->keyControl(DIRECTION_4::LEFT);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _player->keyControl(DIRECTION_4::RIGHT);
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _player->keyControl(DIRECTION_4::TOP);
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _player->keyControl(DIRECTION_4::BOTTOM);
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) MakeBoom(_player->getPlayerTileIndex().x, _player->getPlayerTileIndex().y);
}


void GameObject::setAlpha(int Num)
{
	for (int i = 0; i < _vTileMap.size(); i++)
	{
		_vTileMap[i]->setAlpha(Num);
	}
}

bool GameObject::isRhythmFail(void)
{
	if (Sys->getJudgement() == JUDGEMENT::MISS || Sys->getJudgement() == JUDGEMENT::FAIL) { return true; }
	else return false;
}

void GameObject::setVolume(void)
{
	std::vector<int> _vRange;
	int RangeX, RangeY;
	int playerX = _player->getPlayerTileIndex().x;
	int playerY = _player->getPlayerTileIndex().y;

	int min = 16;
	int temp;

	for (int i = 0; i < _vNpc.size(); i++)
	{
		temp = abs(playerX - _vNpc[i]->getNpcPosX()) + abs(playerY - _vNpc[i]->getNpcPosY());
		if (temp < min) min = temp;
	}

	float n = 1.0f - float(min - 1) / 15.0f;
	if (n > 1) n = 1;
	Sys->shopMusicVolumeSetting(n);
}

void GameObject::MonsterHunt(void)
{
	int idx, idy;

	for (int i = 0; i < _vMonster.size(); i++)
	{
		if (_vMonster[i]->getCurrentHP() <= 0)
		{
			idx = _vMonster[i]->getIdMonster().x;
			idy = _vMonster[i]->getIdMonster().y;

			if (GLOBALDATA->getBunGuck() == 1) GLOBALDATA->setBunGuck(2);
			else if (GLOBALDATA->getBunGuck() == 2) GLOBALDATA->setComboCount(GLOBALDATA->getComboCount() + 1);
			if (GLOBALDATA->getComboCount() >= 4) GLOBALDATA->setBunGuck(3);

			_vTileMap[idx + idy*_TileNum.x]->addGold(_vMonster[i]->getMonsterGold() * GLOBALDATA->getBunGuck());
			_vTileMap[idx + idy*_TileNum.x]->deleteMonster();
			RELEASE_DELETE(_vMonster[i]);
			_vMonster.erase(_vMonster.begin() + i);
			break;
		}
	}
}

void GameObject::updateKeyBuffer()
{
	if (_keybuffer.isActive)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP)){ _keybuffer.up = true;  _turnActive = true; }
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)){ _keybuffer.down = true; _turnActive = true; }
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)){ _keybuffer.left = true; _turnActive = true; }
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)){ _keybuffer.right = true; _turnActive = true; }
	}
	else
	{
		_keybuffer = tagKeyBuffer(false);
	}

}

void GameObject::setTorchLightPower(void)
{
	if (_player->getSight() == 0)
	{
		_sightPower = 6;
		_torchPower = 0;
	}
	else if (_player->getSight() == 1)
	{
		_sightPower = 8;
		_torchPower = 5;
	}
	else if (_player->getSight() == 2)
	{
		_sightPower = 9;
		_torchPower = 6;
	}
}

void GameObject::distructContainer(void)
{
	for (int i = 0; i < _vCon.size(); i++)
	{
		if (_vCon[i]->getOpen())
		{
			int idx, idy;
			idx = _vCon[i]->getIdPoint().x;
			idy = _vCon[i]->getIdPoint().y;

			_vTileMap[idx + idy * _TileNum.x]->setObject(_vCon[i]->getItem());
			_vItem.push_back(_vCon[i]->getItem());
			_vTileMap[idx + idy * _TileNum.x]->deleteContainer();
			RELEASE_DELETE(_vCon[i]);
			_vCon.erase(_vCon.begin() + i);

			break;
		}
	}
}