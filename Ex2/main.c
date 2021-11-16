//-------------------------------------------------------------//
// ----------------------LIBRARY INCLUDES--------------------- //
//-------------------------------------------------------------//

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-------------------------------------------------------------//
// ----------------------PROJECT INCLUDES--------------------- //
//-------------------------------------------------------------//

#include "CreateAThread.h"
#include "HardCodedData.h"
#include "HardCodedDataForThread.h"
#include "inputFilesCalc.h"


int main(int argc, char* argv[]) {

    // check that the arguments are suitable. if not, exit program.
    //check_arguments(argc, argv);

    // Parse arguments for mode of operation, num of threades and key.
    //parse_arguments(&mode, &threads_required, &key, argv);

    
    MATH_THREAD_params_t* p_params;
    int returned_value;

    p_params = (MATH_THREAD_params_t*)malloc(sizeof(MATH_THREAD_params_t));
    if (NULL == p_params)
    {
        printf("Error when allocating memory");
        return ERROR_CODE;
    }
    int number_of_schools = atoi(argv[1]);
    p_params->real_weight = atoi(argv[2]);
    p_params->human_weight = atoi(argv[3]);
    p_params->english_weight = atoi(argv[4]);
    p_params->eval_weight = atoi(argv[5]);

 
    //calc_avg_for_school(p_params);

    returned_value = create_thread(p_params);

    // Close files
    free(p_params);

    return SUCCESS_CODE;
}