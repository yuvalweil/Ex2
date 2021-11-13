#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include "HardCodedData.h"
#include <stdbool.h>
#include <Windows.h> 

// Function Declarations

void create_input_files_for_read(HANDLE hRealFile, HANDLE hHumanFile, HANDLE hEngFile, HANDLE hEvalFile, char* school_num);
void create_file_for_read(HANDLE hFile, char* fileName);


// Function description:


void create_input_files_for_read(HANDLE hRealFile, HANDLE hHumanFile, HANDLE hEngFile, HANDLE hEvalFile,char *school_num)
{
	char realFileName[100]; //TODO: alocate memory
	strcpy(realFileName, "./Real/Real");
	strcat(realFileName, school_num);
	strcat(realFileName, ".txt");
	create_file_for_read(hRealFile, realFileName);
}

void create_file_for_read(HANDLE hFile, char* fileName) 
{
	DWORD dwBytesRead;
	hFile = CreateFileA(fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
// Checks if we failed to open file
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("Failed to create or open file");
			exit(1);
		}
}















//void CreateAndReadFile(HANDLE hFile, char* buffer, DWORD dwBytesToRead, char* fileName, int offset)
//{
//	DWORD dwBytesRead;
//	hFile = CreateFileA(fileName,
//		GENERIC_READ,
//		FILE_SHARE_READ,
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//	// Checks if we failed to open file
//	if (hFile == INVALID_HANDLE_VALUE)
//	{
//		printf("Failed to create or open file");
//		exit(1);
//	}
//	if (offset != 0)
//	{
//		set_new_handel_position(hFile, offset);
//	}
//	BOOL bFile = ReadFile(hFile,
//		(void*)buffer,
//		dwBytesToRead,
//		&dwBytesRead,
//		NULL);
//	if (bFile == FALSE)
//	{
//		printf("Failed to write file");
//		exit(1);
//	}
//	if (dwBytesRead > 0)
//	{
//		buffer[dwBytesRead] = '\0';
//	}
//	CloseHandle(hFile);
//}
//
////Function description:
////Creates or opens a file, change the HANDLE position if necessary and writes the contents of the buffer to a file
//void CreateAndWriteFile(HANDLE hFile, char* buffer, DWORD dwBytesToWrite, char* fileName, int offset)
//{
//	DWORD dwBytesWritten = 0;
//	hFile = CreateFileA(fileName,
//		GENERIC_WRITE,
//		FILE_SHARE_WRITE,
//		NULL,
//		OPEN_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//	// Checks if we failed to open file
//	if (hFile == INVALID_HANDLE_VALUE)
//	{
//		printf("Failed to create or open file");
//		exit(1);
//	}
//	if (offset != 0)
//	{
//		set_new_handel_position(hFile, offset);
//	}
//	BOOL bFile = WriteFile(hFile,
//		(void*)buffer,
//		dwBytesToWrite,
//		&dwBytesWritten,
//		NULL); // need change to &ol
//	if (bFile == FALSE)
//	{
//		printf("Failed to write file");
//		exit(1);
//	}
//	if (dwBytesWritten > 0)
//	{
//		buffer[dwBytesWritten] = '\0';
//	}
//	CloseHandle(hFile);
//}
//
//
////Function description:
////Moves the file pointer of the specified file position
//void set_new_handel_position(HANDLE hFile, int offset)
//{
//	DWORD fPtr = SetFilePointer(hFile, offset, NULL, FILE_BEGIN);
//	if (fPtr == INVALID_SET_FILE_POINTER)
//	{
//		printf("Failure to change pointer position");
//		exit(1);
//	}
//}
//
//
//
//
