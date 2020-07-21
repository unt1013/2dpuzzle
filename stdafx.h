#pragma warning(disable : 4995)
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "define_enum.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "utils.h"
#include "txtData.h"
#include "keyAniManager.h"
#include "iniDataManager.h"


#define GLOBALDATA GlobalData::getSingleton()

using namespace std;
using namespace THETA_UTIL;

#define WINNAME (LPTSTR)(TEXT("2dpuzzle"))	//������ â �̸�
#define WINSTARTX 20						//������ ������ǥX
#define WINSTARTY 20						//������ ������ǥY
#define WINSIZEX 960						//������ ����ũ��
#define WINSIZEY 640						//������ ����ũ��
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//�̱���ȭ ��Ų Ŭ���� ������ȭ
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define INIDATA iniDataManager::getSingleton()


#define SAFE_DELETE(p) {if(p != NULL) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p != NULL) {(p)->release();}}
#define RELEASE_DELETE(p) {if(p != NULL) {(p)->release(); delete(p); (p) = NULL;}}

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
