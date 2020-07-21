#pragma warning(disable : 4995)
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
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

#define WINNAME (LPTSTR)(TEXT("2dpuzzle"))	//윈도우 창 이름
#define WINSTARTX 20						//윈도우 시작좌표X
#define WINSTARTY 20						//윈도우 시작좌표Y
#define WINSIZEX 960						//윈도우 가로크기
#define WINSIZEY 640						//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//싱글톤화 시킨 클래스 디파인화
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
