#ifndef AVERAGE_CALC_THREAD
#define AVERAGE_CALC_THREAD

#include "HardCodedData.h"
DWORD WINAPI AverageThread(LPVOID lpParam);

typedef struct
{
	int weigth_of_real_classes;
	int weigth_of_human_classes;
	int weigth_of_english_classes;
	int weigth_of_school_eval;
	int real_grade;
	int humen_grade;
	int english_grade;
	int eval_grade;
	int result;
} AVERAGE_THREAD_params_t;

#endif // AVERAGE_CALC_THREAD