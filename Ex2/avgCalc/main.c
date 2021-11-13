#include <stdio.h>
#include <stdlib.h>
//#include "HardCodedData.h"
#include "IO.h"
#include <Windows.h> 


struct Student {
	int real_grade;
	int humen_grade;
	int eng_grade;
	int eval_grade;
	int student_avg;
} student;


void main(int argc, char* argv[])
{
	char* school_num = "0";
	int real_weight = 40;
	int human_weight = 35;
	int english_weight = 20;
	int eval_weight = 5;
	HANDLE hRealFile = NULL;
	HANDLE hHumanFile = NULL;
	HANDLE hEngFile = NULL;
	HANDLE hEvalFile = NULL;
	HANDLE hResultFile = NULL;
	create_input_files_for_read(hRealFile, hHumanFile, hEngFile, hEvalFile, school_num);


	//char buffer[NUM_OF_BYTES_FOR_SINGEL_CHECKS + 1];
	//DWORD dwBytesToRead = NUM_OF_BYTES_FOR_SINGEL_CHECKS;  //-1 for null terminator 
	//int offset = atoi(argv[2]);
	//CreateAndReadFile(hInputFile, buffer, dwBytesToRead, argv[1], offset);
	//message_handling(argv, buffer);
	//exit(0);
}


