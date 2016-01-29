#pragma once
#include "stdafx.h"
class CFileReader
{
public:
	BOOL ReadFile2(LPCSTR filepath, TCHAR *&);
	BOOL ReadRow(LPCSTR filepath, TCHAR *&, int row);
	BOOL WriteRow(LPCSTR file, TCHAR *& text);
	BOOL ReplaceFileContent(LPCSTR file, TCHAR *& text);
	BOOL ReplaceString(TCHAR *&, LPSTR newContent);
	CFileReader();
	virtual ~CFileReader();
};

