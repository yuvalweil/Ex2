//-------------------------------------------------------------//
// ----------------------LIBRARY INCLUDES--------------------- //
//-------------------------------------------------------------//

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//-------------------------------------------------------------//
// ----------------------PROJECT INCLUDES--------------------- //
//-------------------------------------------------------------//

#include "AverageCalcThread.h"
#include "CreateAThread.h"
#include "HardCodedData.h"


int main(int argc, char* argv[]) {

    // check that the arguments are suitable. if not, exit program.
    //check_arguments(argc, argv);

    // Parse arguments for mode of operation, num of threades and key.
    //parse_arguments(&mode, &threads_required, &key, argv);

    // File parameters
    AVERAGE_THREAD_params_t* p_params;

    p_params = (AVERAGE_THREAD_params_t*)malloc(sizeof(AVERAGE_THREAD_params_t));
    if (NULL == p_params)
    {
        printf("Error when allocating memory");
        return ERROR_CODE;
    }
    int number_of_schools = atoi(argv[1]);
    int weight_of_real_classes = atoi(argv[2]);
    int weight_of_human_classes = atoi(argv[3]);
    int weight_of_english_class = atoi(argv[4]);
    int weight_of_school_eval = atoi(argv[5]);

    //open the files

    //put the grades in p_params fields

    // thread manager function
    int create_thread(p_params);

    // Close files

    return SUCCESS_CODE;
}