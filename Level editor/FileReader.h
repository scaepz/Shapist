#pragma once
#include "stdafx.h"
class CFileReader
{
public:
	BOOL ReadFile2(LPCSTR filepath, TCHAR *&);
	void WriteNewRowToFile(LPCSTR file, TCHAR *& text);
	BOOL ReplaceFileContent(LPCSTR file, TCHAR *& text);
	BOOL ReplaceString(TCHAR *&, LPSTR newContent);
	CFileReader();
	virtual ~CFileReader();
};

