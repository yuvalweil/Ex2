#ifndef CREATE_A_THREAD
#define CREATE_A_THREAD

#include "AverageCalcThread.h"
#include "CreateAThread.h"
#include "HardCodedData.h"

// Constants -------------------------------------------------------------------
#define NUM_THREADS 10
#define ERROR_CODE ((int)(-1))
#define SUCCESS_CODE ((int)(0))

int create_thread(AVERAGE_THREAD_params_t* p_params);

#endif // CREATE_A_THREAD