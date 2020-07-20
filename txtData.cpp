#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{

	return S_OK;
}

void txtData::release()
{

}

//세이브
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[def_txtDataBuffer] = { '\0', };
	DWORD write;

	strncpy_s(str, def_txtDataBuffer, vectorArrayCombine(vStr), def_txtDataBuffer-2);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, def_txtDataBuffer, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[def_txtDataBuffer] = { '\0', };

	ZeroMemory(str, sizeof(str));

	for (unsigned int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, def_txtDataBuffer, vArray[i].c_str(), def_txtDataSingleBuffer - 2);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}


//로드
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;

	char str[def_txtDataBuffer] = { '\0', };
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, def_txtDataBuffer, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	if (token != NULL) vArray.push_back(token);
	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
