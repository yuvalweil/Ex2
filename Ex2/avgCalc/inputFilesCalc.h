#ifndef INPUT_FILES_CALC
#define INPUT_FILES_CALC

#include "HardCodedDataForThread.h"
#include <Windows.h> 

void calc_avg_for_school(HANDLE hRealFile, HANDLE hHumanFile, HANDLE hEngFile, HANDLE hEvalFile, HANDLE hResultFile, Student students[], MATH_THREAD_params_t* p_thread_params);


#endif
