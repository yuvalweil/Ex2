#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFilesCalc.h"
#include <Windows.h> 
#include "HardCodedDataForThread.h"

//void main(MATH_THREAD_params_t* p_thread_params)
void main()
{
	//////////////////////// temp ////////////////////////////
	MATH_THREAD_params_t* p_thread_params;
	p_thread_params = (MATH_THREAD_params_t*)malloc(sizeof(MATH_THREAD_params_t));
	p_thread_params->real_weight = 40;
	p_thread_params->human_weight = 35;
	p_thread_params->english_weight = 20;
	p_thread_params->eval_weight = 5;
	p_thread_params->school_num = 0;
	//////////////////////// temp ////////////////////////////

	HANDLE *hRealFile = NULL;
	HANDLE *hHumanFile = NULL;
	HANDLE *hEngFile = NULL;
	HANDLE *hEvalFile = NULL;
	HANDLE *hResultFile = NULL;
	Student students[100]; //TODO calc num of students and alocate + free
	calc_avg_for_school(hRealFile, hHumanFile, hEngFile, hEvalFile, hResultFile, &students, p_thread_params);

	free(p_thread_params);
}


