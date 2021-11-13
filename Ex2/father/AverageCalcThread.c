// Average_Thread.c

// Includes --------------------------------------------------------------------

#include <windows.h>
#include "AverageCalcThread.h"
#include "HardCodedData.h"


// Function Definitions --------------------------------------------------------
void average_calc(AVERAGE_THREAD_params_t* p_params);

DWORD WINAPI AverageThread(LPVOID lpParam)
{
	DWORD wait_code;
	BOOL ret_val;
	HANDLE average_mutex_handle;
	AVERAGE_THREAD_params_t* p_params;

	average_mutex_handle = OpenMutex(
		SYNCHRONIZE,         /*  default security attributes */
		FALSE,               /*  Set handle inheritance to FALSE. */
		P_AVERAGE_MUTEX_NAME); /* This MUST be the EXACT same name as was used when */
							 /* the mutex was created. To save heartache, use a string */
							 /* constant (as is done here). */

	/*
	* Take ownership of the mutex
	* Wait for the mutex to become available, then take ownership.
	* If the reurn value WaitForSingleObject is WAIT_OBJECT_0,
	* it means that the calling thread now has ownership of the mutex.
	* If the mutex is not available when calling WaitForSingleObject,
	* the OS will move the state of the thread from ready/running to waiting.
	* When the mutex is released by the other thread using it, the state
	* of the thread will change back from waiting to ready.
	*/
	wait_code = WaitForSingleObject(average_mutex_handle, INFINITE);
	if (WAIT_OBJECT_0 != wait_code)
	{
		printf("Error when waiting for mutex\n");
		return ERROR_CODE;
	}

	/*
	* Critical Section
	* We can now safely access the shared resource.
	*/
	p_params = (AVERAGE_THREAD_params_t*)lpParam;

	average_calc(p_params);

	/*
	* Release mutex
	* Sharing is caring
	*/
	ret_val = ReleaseMutex(average_mutex_handle);
	if (FALSE == ret_val)
	{
		printf("Error when releasing\n");
		return ERROR_CODE;
	}

	return SUCCESS_CODE;


	/* Check if lpParam is NULL */
	if (NULL == lpParam)
	{
		return MATH_THREAD__CODE_NULL_PTR;
	}


	return AVERAGE_THREAD__CODE_SUCCESS;
}

void average_calc(AVERAGE_THREAD_params_t* p_params) {
	int result = p_params->real_grade * p_params->weigth_of_real_classes / 100 + p_params->humen_grade * p_params->weigth_of_human_classes / 100 + p_params->english_grade * p_params->weigth_of_english_classes / 100 + p_params->eval_grade * p_params->weigth_of_school_eval / 100;
	p_params->real_grade = result;
}