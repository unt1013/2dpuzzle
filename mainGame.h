#pragma once
#pragma comment(lib, "WindowsCodecs.lib")
#include "gameNode.h"
#include "wincodec.h"

//#include <commdlg.h> OPENFILE 사용시 주석 해제 

class mainGame : public gameNode
{
private:;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void SceneInit(void);

	mainGame();
	~mainGame();
};

