#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

const int def_txtDataBuffer = 16384;
const int def_txtDataSingleBuffer = 128;

class txtData : public singletonBase<txtData>
{
public:
	HRESULT init();
	void release();

	//세이브
	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//로드
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);


	txtData();
	~txtData();
};

