#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{

	return S_OK;
}

void imageManager::release()
{

	
}

//빈 비트맵 이미지
image* imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//파일 이미지
image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;

}

image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;

}

image* imageManager::addPngImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//프레임 이미지
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;

}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;

}

image* imageManager::addFramePngImage(string strKey, const CHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//만약 이미지가 있다면 그냥 그걸 반환
	if (img) return img;

	//이미지가 없다면
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//map에서 insert할때 make_pair(first, second) <--- 알아서 형을 찾아서 추가
	//					pair(자료형, 자료형)<first, second> <-- 형 지정하고 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//key가 맵의 끝이 아니라면 == 키 값을 찾았으면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}


BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;

}


void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);

}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);

}

void imageManager::stretchRender(string strKey, HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH)
{
	image* img = findImage(strKey);

	img->stretchRender(hdc, destX, destY, destW, destH, sourX, sourY, sourW, sourH);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
void imageManager::frameInsideRender(string strKey, HDC hdc, int destX, int destY, int subtractX, int subtractY)
{
	image* img = findImage(strKey);
	if (img) img->frameInsideRender(hdc, destX, destY, subtractX, subtractY);
}
void imageManager::frameInsideRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int subtractX, int subtractY)
{
	image* img = findImage(strKey);
	if (img) img->frameInsideRender(hdc, destX, destY, currentFrameX, currentFrameY, subtractX, subtractY);
}
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc,destX, destY, sourX,sourY,sourWidth,sourHeight,alpha);
}

void imageManager::stretchAlphaRender(string strKey, HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->stretchAlphaRender(hdc, destX, destY, destW, destH, sourX, sourY, sourW, sourH, alpha);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY,alpha);
}
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY,alpha);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc,drawArea, offSetX,offSetY, alpha);
}