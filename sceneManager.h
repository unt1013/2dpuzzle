#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	// iOS -> vector NSMUTABLEARRAY // map -> NSMUTBLEDICTIONARY

	//          first(Ű ��)    second(�ڷ�)
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

	//�� �߰��ϴ� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);//�̰� ����­��

	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	//�� �������� �Լ�
	gameNode* GetScene(string sceneName); //�ϴ� �̰� ���߿� �����

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager();
	~sceneManager();
};

