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
		return FALSE;
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
		return TRUE;
	}
	else
	{
		CloseHandle(hFile);
		return FALSE;
	}

}
BOOL CFileReader::WriteRow(LPCSTR file, TCHAR * &content)
{
	HANDLE hFile;
	DWORD dwFileSize = 0;
	TCHAR newRow[2] = { '\r', '\n' };

	hFile = CreateFile(file,               // file to open
		GENERIC_WRITE,          // open for write
		FILE_SHARE_WRITE,       // share for writing
		NULL,                  // default security
		OPEN_ALWAYS,         // creates new if does not exist
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	//Move cursor to end of file
	SetFilePointer(hFile, GetFileSize(hFile, NULL), NULL, FILE_BEGIN);

	DWORD dwBytesWritten;
	if (WriteFile(hFile, newRow, 2, &dwBytesWritten, NULL))
	{
		if (WriteFile(hFile, content, strlen(content), &dwBytesWritten, NULL))
		{
			CloseHandle(hFile);
			return TRUE;
		}
		else
		{
			CloseHandle(hFile);
			return FALSE;
		}
	}
	else
	{
		CloseHandle(hFile);
		return FALSE;
	}
}
BOOL CFileReader::ReplaceFileContent(LPCSTR file, TCHAR * &content)
{
	HANDLE hFile;
	DWORD dwFileSize = 0;

	hFile = CreateFile(file,               // file to open
		GENERIC_WRITE,          // open for write
		FILE_SHARE_WRITE,       // share for writing
		NULL,                  // default security
		CREATE_ALWAYS,         // creates always -> replace old file
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwBytesWritten;
	if (WriteFile(hFile, content, strlen(content), &dwBytesWritten, NULL))
	{
		CloseHandle(hFile);
		return TRUE;
	}
	else
	{
		CloseHandle(hFile);
		return FALSE;
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
	return TRUE;
}

BOOL CFileReader::ReadRow(LPCSTR filepath, TCHAR *& file, int row)
{
	if (!ReadFile2(filepath, file))
	{
		return false;
	}
	int currentRow = 0;
	BOOL foundRow = FALSE;
	TCHAR * result = new TCHAR[512];
	int currentRowIndex = 0;

	for (int i = 0; i < strlen(file); i++)
	{
		if (currentRow == row)
		{
			foundRow = TRUE;
			if (file[i] != '\n')
			{
				result[currentRowIndex] = file[i];
				currentRowIndex++;
			}
		}
		if (file[i] == '\n') currentRow++;
		if (currentRow > row) break;
	}
	if (foundRow == TRUE)
	{
		result[currentRowIndex] = '\0';
		delete file;

		//make new string instead of result because it is unnecessarily long
		file = new TCHAR[strlen(result)];
		for (int i = 0; i < strlen(result); i++)
		{
			file[i] = result[i];
		}
		file[strlen(result)] = '\0';

		delete result;

		return TRUE;
	}
	else return FALSE;
}