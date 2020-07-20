#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, string soundName, bool background, bool loop)
{
	_kind = LOAD_KIND_SOUND;
	memset(&_soundResource, 0, sizeof(tagSoundResource));

	_soundResource.keyName = keyName;
	_soundResource.soundName = soundName;
	_soundResource.background = background;
	_soundResource.loop = loop;

	return S_OK;
}


loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage("LoadingBackground","Image/Scene/LoadingScene.bmp", WINSIZEX, WINSIZEY,true,RGB(255,0,255));
	_loadingnow = IMAGEMANAGER->addImage("LoadingNow", "Image/Scene/LoadingFont.bmp", 200, 40, true, RGB(0, 0, 0));
	_loadingcomplete = IMAGEMANAGER->addImage("LoadingComplete", "Image/Scene/LoadingComplete.bmp", 657, 54, true, RGB(255, 0, 255));

	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
}

void loading::update()
{
}

void loading::render()
{
	_background->render(getMemDC(), 0, 0);
	_loadingnow->render(getMemDC(), WINSIZEX /2 - 100 ,WINSIZEY - 50 );

	//renderLoadingList();
}


void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}
void loading::loadSound(string keyName, string soundName, bool background, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, soundName, background, loop);

	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height,
			img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height,
			img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height,
			img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height,
			img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_SOUND:
	{
		tagSoundResource sound = item->getSoundResource();
		SOUNDMANAGER->addSound(sound.keyName, sound.soundName, sound.background, sound.loop);
	}
	break;
	}

	_currentGauge++;

	return FALSE;
}

void loading::renderLoadingList()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return;
	}
	for (int i = _currentGauge; i >= 0; --i)
	{
		loadItem* item = _vLoadItem[i];
		string str;

		switch (item->getLoadingKind())
		{
		case LOAD_KIND_SOUND:
			str = item->getSoundResource().keyName;
			break;
		default:
			str = item->getImageResource().keyName;
			break;
		}

		str += " OK!";

		int printY = WINSIZEY - 100 - 20 * (_currentGauge - i);
		if (printY < 200) break;

		TextOutA(getMemDC(),
			20,
			printY,
			str.c_str(),
			strlen(str.c_str()));
	}


}