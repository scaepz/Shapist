#pragma once
#include "FileReader.h"
class CTextureManager
{
public:
	CTextureManager();
	BOOL AddTexture(LPSTR name, LPSTR path);
	int ExistsTexture(LPSTR name);
	BOOL RemoveTexture(LPSTR name);
	BOOL GetTexturePath(LPSTR name, TCHAR * & path);
	virtual ~CTextureManager();
private:
	LPSTR textureFile = "data/textures/texturelist.txt";
};

