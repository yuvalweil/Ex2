// ThreadParametersDemonstration.c

/*
* This program serves as a demonstration on how to pass parameters to a thread
* during thread creation.
*/

// Includes --------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "CreateAThread.h"
#include "HardCodedDataForThread.h"
#include "inputFilesCalc.h"
#include "HardCodedData.h"

/* The name of the mutex */

// Function Declarations -------------------------------------------------------
static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id);

// Function Definitions --------------------------------------------------------

int create_thread(MATH_THREAD_params_t* p_params)
{
	int number_of_schools = p_params->number_of_schools;
	HANDLE p_thread_handles[30]; //use malloc
	DWORD p_thread_ids[30]; //use malloc
	DWORD wait_code;
	BOOL ret_val;
	size_t i;
	HANDLE average_mutex_handle = NULL;
	DWORD exit_code;


	//average_mutex_handle = CreateMutex(
	//	NULL,					/* default security attributes */
	//	FALSE,					/* initially not owned */
	//	P_AVERAGE_MUTEX_NAME);	/* named mutex */

	//if (NULL == average_mutex_handle)
	//{
	//	printf("Error when creating mutex: %d\n", GetLastError());
	//	return ERROR_CODE;
	//}

	for (int i = 0; i < number_of_schools; i++)
	{
		p_params->school_num = i;
		p_thread_handles[i] = CreateThreadSimple(calc_avg_for_school, p_params, &p_thread_ids[i]);
		if (NULL == p_thread_handles[i])
		{
			printf("Error when creating thread: %d\n", GetLastError());
			return ERROR_CODE;
		}

		/* Wait */
		if (i >= MAX_NUM_THREADS) {
			wait_code = WaitForMultipleObjects(MAX_NUM_THREADS, &p_thread_handles[i-MAX_NUM_THREADS], FALSE, INFINITE);
			if (WAIT_OBJECT_0 > wait_code || i < wait_code)
			{
				printf("Error when waiting\n");
				return ERROR_CODE;
			}
		}

		/* Check the DWORD returned by MathThread */
		ret_val = GetExitCodeThread(p_thread_handles[i], &exit_code);
		if (0 == ret_val)
		{
			printf("Error when getting thread exit code\n");
		}
		/* Print results, if thread succeeded */
		if (AVERAGE_THREAD__CODE_SUCCESS != exit_code)
		{
			printf("Error in thread: %d\n", exit_code);
		}

		/* Close thread handle */
		ret_val = CloseHandle(p_thread_handles[i]);
		if (false == ret_val)
		{
			printf("Error when closing\n");
			return ERROR_CODE;
		}

	}

	return SUCCESS_CODE;
}

static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id)
{
	HANDLE thread_handle;

	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	thread_handle = CreateThread(
		NULL,                /*  default security attributes */
		0,                   /*  use default stack size */
		p_start_routine,     /*  thread function */
		p_thread_parameters, /*  argument to thread function */
		0,                   /*  use default creation flags */
		p_thread_id);        /*  returns the thread identifier */

	return thread_handle;
}
