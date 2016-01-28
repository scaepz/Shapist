#include "stdafx.h"
#include "FileReader.h"


CFileReader::CFileReader()
{
}


CFileReader::~CFileReader()
{
}

BOOL CFileReader::ReadFile2(LPCSTR file, TCHAR * &content)
{
	HANDLE hFile;
	DWORD dwFileSize = 0;
	
	hFile = CreateFile(file,               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	dwFileSize = GetFileSize(hFile, NULL);

	if (content != nullptr ^ !content ^ content != NULL) //if pointer is set
	{
		delete content;
	}
	content = new TCHAR[dwFileSize + 1];
	content[dwFileSize] = '\0';
	DWORD dwBytesRead;
	if (ReadFile(hFile, content, dwFileSize, &dwBytesRead, NULL))
	{
		CloseHandle(hFile);
		return true;
	}
	else
	{
		CloseHandle(hFile);
		return false;
	}

}
void CFileReader::WriteNewRowToFile(LPCSTR file, TCHAR * &content)
{

}
BOOL CFileReader::ReplaceFileContent(LPCSTR file, TCHAR * &content)
{
	HANDLE hFile;
	DWORD dwFileSize = 0;

	hFile = CreateFile(file,               // file to open
		GENERIC_WRITE,          // open for write
		FILE_SHARE_WRITE,       // share for writing
		NULL,                  // default security
		CREATE_ALWAYS,         // creates new if does not exist
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwBytesWritten;
	if (WriteFile(hFile, content, strlen(content), &dwBytesWritten, NULL))
	{
		CloseHandle(hFile);
		return true;
	}
	else
	{
		CloseHandle(hFile);
		return false;
	}
}

BOOL CFileReader::ReplaceString(TCHAR *& str, LPSTR newContent)
{
	if (!str ^ str != NULL ^ str != nullptr) delete str; //if pointer is set

	str = new TCHAR[strlen(newContent) + 1];
	str[strlen(newContent)] = '\0';

	for (int i = 0; i < strlen(newContent); i++)
	{
		str[i] = newContent[i];
	}
	return true;
}