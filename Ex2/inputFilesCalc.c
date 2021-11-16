#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h> 
#include "HardCodedDataForThread.h"
#include <string.h>
#include "HardCodedData.h"



// Function Declarations

DWORD WINAPI calc_avg_for_school(LPVOID lpParam);
HANDLE create_file_for_read(HANDLE hFile, char* fileName);
int read_file_and_update_students(HANDLE hFile, struct Student* students, enum typeGrade type);
int split_grades(char* buffer, struct Student* students, DWORD dwBytesToRead, enum typeGrade type);
void calc_avg_grade(Student* students, int num_of_students, MATH_THREAD_params_t* p_thread_params);
HANDLE create_file_for_write(HANDLE hFile, char* fileName);
void write_results_of_school(HANDLE hResultFile, Student* students, int num_of_students);




// Function description:


DWORD WINAPI calc_avg_for_school(LPVOID lpParam)
{
	MATH_THREAD_params_t* p_thread_params = NULL;
	p_thread_params = (MATH_THREAD_params_t*)lpParam;
	enum typeGrade type;
	int num_of_students;
	int full_length = 0;
	HANDLE* hRealFile = NULL;
	HANDLE* hHumanFile = NULL;
	HANDLE* hEngFile = NULL;
	HANDLE* hEvalFile = NULL;
	HANDLE* hResultFile = NULL;
	Student students[100]; //TODO calc num of students and alocate + free

	int length = snprintf(NULL, 0, "%d", p_thread_params->school_num);
	char* s_school_num = malloc(length + 1);
	snprintf(s_school_num, length + 1, "%d", p_thread_params->school_num);

	type = 1;
	full_length = strlen("./Real/Real") + length + strlen(".txt");
	char* realFileName = (char*)malloc(full_length * (sizeof(char)));
	strcpy(realFileName, "./Real/Real");
	strcat(realFileName, s_school_num);
	strcat(realFileName, ".txt");
	hRealFile = create_file_for_read(hRealFile, realFileName);
	num_of_students = read_file_and_update_students(hRealFile, students, type);

	type = 2;
	full_length = strlen("./Human/Human") + length + strlen(".txt");
	char* umanFileName = (char*)malloc(full_length * (sizeof(char)));
	strcpy(umanFileName, "./Human/Human");
	strcat(umanFileName, s_school_num);
	strcat(umanFileName, ".txt");
	hHumanFile = create_file_for_read(hHumanFile, umanFileName);
	read_file_and_update_students(hHumanFile, students, type);

	type = 3;
	full_length = strlen("./Eng/Eng") + length + strlen(".txt");
	char* engFileName = (char*)malloc(full_length * (sizeof(char)));
	strcpy(engFileName, "./Eng/Eng");
	strcat(engFileName, s_school_num);
	strcat(engFileName, ".txt");
	hEngFile = create_file_for_read(hEngFile, engFileName);
	read_file_and_update_students(hEngFile, students, type);

	type = 4;
	full_length = strlen("./Eval/Eval") + length + strlen(".txt");
	char* evalFileName = (char*)malloc(full_length * (sizeof(char)));
	strcpy(evalFileName, "./Eval/Eval");
	strcat(evalFileName, s_school_num);
	strcat(evalFileName, ".txt");
	hEvalFile = create_file_for_read(hEvalFile, evalFileName);
	read_file_and_update_students(hEvalFile, students, type);

	calc_avg_grade(students, num_of_students, p_thread_params);

	full_length = strlen("./Results/Results") + length + strlen(".txt");
	char* resultFileName = (char*)malloc(full_length * (sizeof(char)));
	strcpy(resultFileName, "./Results/Results");
	strcat(resultFileName, s_school_num);
	strcat(resultFileName, ".txt");
	hResultFile = create_file_for_write(hResultFile, resultFileName);
	write_results_of_school(hResultFile, students, num_of_students);

	free(s_school_num);
	free(realFileName);
	free(hHumanFile);
	free(engFileName);
	free(evalFileName);
	free(resultFileName);

	return AVERAGE_THREAD__CODE_SUCCESS;
}

HANDLE create_file_for_read(HANDLE hFile, char* fileName)
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
	return hFile;
}

HANDLE create_file_for_write(HANDLE hFile, char* fileName)
{
	DWORD dwBytesWritten = 0;
	hFile = CreateFileA(fileName,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	// Checks if we failed to open file
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Failed to create or open file");
		exit(1);
	}
	return hFile;
}

int read_file_and_update_students(HANDLE hFile, Student* students, enum typeGrade type)
{
	DWORD dwBytesRead;
	LPDWORD lpFileSizeHigh = NULL;
	DWORD dwBytesToRead = GetFileSize(hFile, lpFileSizeHigh);
	if (dwBytesToRead == INVALID_FILE_SIZE)
	{
		printf("Failed to get size of file");
		exit(1);
	}
	char* buffer = (char*)malloc(sizeof(char) * dwBytesToRead);
	BOOL bFile = ReadFile(hFile,
		(void*)buffer,
		dwBytesToRead,
		&dwBytesRead,
		NULL);
	if (bFile == FALSE)
	{
		printf("Failed to write file");
		exit(1);
	}
	int num_of_students = split_grades(buffer, students, dwBytesToRead, type);
	free(buffer);
	CloseHandle(hFile);
	return num_of_students;
}

int split_grades(char* buffer, Student* students, DWORD dwBytesToRead, enum typeGrade type)
{
	char temp_grade[4]; //max 3 digits + '\0'
	unsigned int i, j;
	int student_number = -1;
	for (i = 0; i < dwBytesToRead; i++)
	{
		if (buffer[i] == '\n')
		{
			continue;
		}
		for (j = 0; (buffer[i] != '\r'); j++)
		{
			temp_grade[j] = buffer[i++];
		}
		temp_grade[j] = '\0';
		student_number++;
		switch (type)
		{
		case Real:
			students[student_number].real_grade = atoi(temp_grade);
			break;
		case Human:
			students[student_number].humen_grade = atoi(temp_grade);
			break;
		case Eng:
			students[student_number].eng_grade = atoi(temp_grade);
			break;
		case Eval:
			students[student_number].eval_grade = atoi(temp_grade);
			break;
		default:
			break;
		}
	}
	return student_number;
}

void calc_avg_grade(Student* students, int num_of_students, MATH_THREAD_params_t* p_thread_params)
{
	int temp_avg_grade = 0;
	for (int i = 0; i < num_of_students + 1; i++)
	{
		temp_avg_grade = students[i].real_grade * p_thread_params->real_weight;
		temp_avg_grade += students[i].humen_grade * p_thread_params->human_weight;
		temp_avg_grade += students[i].eng_grade * p_thread_params->english_weight;
		temp_avg_grade += students[i].eval_grade * p_thread_params->eval_weight;
		students[i].student_avg = temp_avg_grade / 100;
	}
	return;
}

void write_results_of_school(HANDLE hResultFile, Student* students, int num_of_students)
{
	LPDWORD lpNumberOfBytesWritten;
	for (int i = 0; i < num_of_students + 1; i++)
	{
		int length = snprintf(NULL, 0, "%d", students[i].student_avg);
		char* temp_buffer = malloc(length + 2);
		snprintf(temp_buffer, length + 1, "%d", students[i].student_avg);
		strcat(temp_buffer, "\n");
		BOOL bFile = WriteFile(hResultFile,
			(void*)temp_buffer,
			length + 1,
			&lpNumberOfBytesWritten,
			NULL);
		if (bFile == FALSE)
		{
			printf("Failed to write file");
			exit(1);
		}
		free(temp_buffer);
	}
	return;
}
