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
		OPEN_EXISTING,         // open only if exists
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	dwFileSize = GetFileSize(hFile, NULL);

	if (content != nullptr ^ !content ^ content != NULL) //if pointer is set
	{
		delete [] content;
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
	if (GetLastError() == ERROR_ALREADY_EXISTS && GetFileSize(hFile, NULL) != 0)
	{
		if (!WriteFile(hFile, newRow, 2, &dwBytesWritten, NULL))
		{
			CloseHandle(hFile);
			return FALSE;
		}
	}

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
	if (!str ^ str != NULL ^ str != nullptr) delete[] str; //if pointer is set

	str = new TCHAR[strlen(newContent) + 1];
	str[strlen(newContent)] = '\0';

	for (int i = 0; i < strlen(newContent); i++)
	{
		str[i] = newContent[i];
	}
	return TRUE;
}
BOOL CFileReader::FileExists(LPSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
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
			if (file[i] != '\r')
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
		if (result[currentRowIndex - 1] == '\n') result[currentRowIndex - 1] = '\0';
		delete []file;

		//make new string instead of result because it is unnecessarily long
		file = new TCHAR[strlen(result)];
		for (int i = 0; i < strlen(result); i++)
		{
			file[i] = result[i];
		}
		file[strlen(result)] = '\0';

		delete []result;

		return TRUE;
	}
	else
	{
		delete[] result;
		delete [] file;
		return FALSE;
	}
}

BOOL CFileReader::RemoveRow(LPCSTR file, int row)
{
	TCHAR *content;
	if (!ReadFile2(file, content))
	{
		return FALSE;
	}
	int currentRow = 0;
	BOOL foundRow = FALSE;

	if (row == 0)
	{
		foundRow = TRUE;
		while (content[0] != '\n' && content[0] != '\0')
		{
			for (int x = 0; x < strlen(content); x++)
			{
				content[x] = content[x + 1];
			}
		}
		if (content[0] == '\n')
		{
			for (int x = 0; x < strlen(content); x++)
			{
				content[x] = content[x + 1];
			}
		}

	}
	else
	for (int i = 0; i < strlen(content); i++)
	{
		if (currentRow == row)
		{
			foundRow = TRUE;
			if (content[i] != '\r')
			{
				for (int x = i; x < strlen(content); x++)
				{
					content[x] = content[x + 1];
				}
				i--;
			}
			else
			{
				break;
			}
		}
		if (content[i] == '\n') 
		{
			currentRow++;
			
			i--;
		}
		if (currentRow > row) break;
	}
	
	if (!foundRow)
	{
		delete[] content;
		return FALSE;
	};
	
	if (ReplaceFileContent(file, content))
	{
		delete[] content;
		return TRUE;
	}
	else
	{
		delete[] content;
		return FALSE;
	}
}