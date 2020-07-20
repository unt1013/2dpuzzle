#include "gameNode.h"
#include "GameTile.h"
#include "MapToolTileMap.h"

#include "MonsterList.h"
#include "Camera.h"

#include "RhythmSystem.h"
#include "SightSystem.h"

#include "GameObjectCommandDefine.h"

class GameObject : public gameNode
{
private:
	player* _player;
	POINT _TileSize;
	POINT _TileNum;
	Camera _camera;

	RhythmSystem* Sys;
	SightSystem* Sys2;
	ItemFactory* _itemFactory;

	std::vector<GameTile*> _vTileMap;
	
	std::vector<Item*> _vItem;
	std::vector<Monster*> _vMonster;
	std::vector<Wall*> _vWall;
	std::vector<Boom*> _vBoom;
	std::vector<container*> _vCon;
	std::vector<traps*> _vTrap;
	std::vector<Shrine*> _vShrine;
	std::vector<Npc*> _vNpc;

	int _sightPower;
	int _torchPower;
	KEYBUF _keybuffer;
		
public:
	HRESULT init(string MapKey, string BgmKey, string ShopkeeperKey, int bpm);
	void release();
	void update();
	void render();
	void Load(string MapKey);

	void PushItemVector(Item* item) { _vItem.push_back(item); }

	void MakeItem(int idx, int idy, MAP_TOOL::Item item);
	void MakeMonster(MAP_TOOL::MONSTER monster, int idx, int idy, DIRECTION_4 direction);
	void MakeNPC(MAP_TOOL::NPC npc, int idx, int idy);
	void MakeWall(MAP_TOOL::WALL wall, int idx, int idy, bool A);
	void MakeContainer(MAP_TOOL::CONTAINER con, int idx, int idy);
	void MakeShrine(MAP_TOOL::SHRINE shrine, int idx, int idy);
	void MakeTrap(MAP_TOOL::TRAP trap, int idx, int idy);
	void MakeBoom(int idx, int idy);

	void PlayerMove(void);
	void BoomUpdate();
	void setAlpha(int Num);

	POINT getTileSize(void) { return _TileSize; }
	POINT getTileNum(void) { return _TileNum; }
	player* getPlayer(void) { return _player; }
	bool isRhythmFail(void);

	std::vector<GameTile*>* getTileMap(void) { return &_vTileMap; }
	std::vector<Monster*>* getvMonster(void) { return &_vMonster; }
	void monsterCollision(void);

	void setVolume(void);
	void distructContainer(void);

	vector<GameTile*> _vOpenList;
	vector<GameTile*>::iterator _viOpenList;

	vector<GameTile*> _vCloseList;
	vector<GameTile*>::iterator _viCloseList;

	GameTile* _startTile;
	GameTile* _endTile;
	GameTile* _currentTile;

	RhythmSystem* getSys(void) { return Sys; }

	int _count;
	bool _start;

	bool _turnActive;

	DIRECTION_4 _direction;
	int _dNum;

	//에이스타에 추가되는 함수들
	vector<GameTile*> addOpenList(GameTile* currentTile);

	DIRECTION_4 Astar(int startIdX, int startIdY, int endIdX, int endIdy, bool canBreakWall);
	void pathFinder(GameTile* currentTile);

	void eraseWallVector(Wall* A);
	void eraseItemVector(Item* A);
	void eraseMonsterVector(Monster* A);
	void eraseTrapVector(traps* A);
	void eraseShrineVector(Shrine* A);
	void eraseBoomVector(Boom* A);

	void deleteWallVector(Wall* A);
	void deleteItemVector(Item* A);
	void deleteMonsterVector(Monster* A);
	void deleteTrapVector(traps* A);
	void deleteShrineVector(Shrine* A);
	void deleteBoomVector(Boom* A);

	void MonsterHunt(void);

	void updateKeyBuffer();
	void setTorchLightPower(void);

	GameObject();
	~GameObject();
};
