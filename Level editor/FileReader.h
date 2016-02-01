#pragma once
#include "stdafx.h"
class CFileReader
{
public:
	BOOL ReadFile2(LPCSTR filepath, TCHAR *&);
	BOOL ReadRow(LPCSTR filepath, TCHAR *&, int row);
	BOOL WriteRow(LPCSTR file, TCHAR *& text);
	BOOL ReplaceFileContent(LPCSTR file, TCHAR *& text);
	BOOL RemoveRow(LPCSTR file, int row);
	BOOL ReplaceString(TCHAR *&, LPSTR newContent);
	BOOL FileExists(LPSTR szPath);
	CFileReader();
	virtual ~CFileReader();
};

