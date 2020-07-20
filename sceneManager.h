#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	// iOS -> vector NSMUTABLEARRAY // map -> NSMUTBLEDICTIONARY

	//          first(키 값)    second(자료)
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;
	static gameNode* _loadingScene;
	static gameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;

	bool _isChangeScene;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가하는 함수
	gameNode* addScene(string sceneName, gameNode* scene);//이거 누가짯냐

	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//씬 가져오는 함수
	gameNode* GetScene(string sceneName); //일단 이거 나중에 만들고

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager();
	~sceneManager();
};

