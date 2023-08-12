#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

/*
With this generator we try to find a testcase having the specific requirements
simply by using bruteforce.

Example Call:
    ./generator1 1000000 q 750 1000
    -> tries to find a testcase input for the quicksort algorithm containing
       1000000 values and being processed in between 750 and 1000 milliseconds.
*/

int main(int argn, char** argv) {
    // check for all present parameters
    if(argn != 5) {
        fprintf(stderr, "Error! Expected parameters <n> <a> <l> <h>\nn:\tnumber of values\na:\talgorithm to use ('i', 'm', 'q', 's')\nl:\tminimum time requirement (ms)\nh:\tmaximum time requirement (ms)\n");
        return 1;
    }

    // speed factor given by 'eval.py' (to have better comparable values)
    double speed_factor = 0.8f;
    int amount_random_tries = 5;

    char* out_file_name = "gentest.in";
    FILE* out_file_ptr;

    struct timeval t_start, t_end;
    double t_duration;

    // read in all parameters ...
    int min, max;
    unsigned long n;
    char* algo;
    char *end_ = NULL;

    n = strtoul(argv[1], &end_, 10);
    algo = argv[2];
    min = atoi(argv[3]);
    max = atoi(argv[4]);

    // Generate command to test runtime on
    char cmd[25];
    strcpy(cmd, "./sortme ");
    strcat(cmd, algo);
    strcat(cmd, " < ");
    strcat(cmd, out_file_name);

    fprintf(stdout, "Debug: cmd:%s\n", cmd);

    // Test sorted input:
    fprintf(stdout, "Testing sorted input values:\n");
    out_file_ptr = fopen(out_file_name, "w");
    if (out_file_ptr == NULL) {
        fprintf(stderr, "ERROR Creating File!\n");
        return 2;
    }

    fprintf(out_file_ptr, "%lu\n", n);
    for (unsigned long j = 0; j < n; j++) {
        fprintf(out_file_ptr, "%lu\n", j);
    }

    fclose(out_file_ptr);

    // time the execution of the algorithm
    // using clock_gettime() would be better practice, but i get weird results using this method.
    // maybe because i am using WSL ...
    // gettimeofday() gets the job done, even tho we are loosing some precision.
    gettimeofday(&t_start, NULL);

    // run the command
    if (system(cmd) > 0) {
        return 3;
    }

    gettimeofday(&t_end, NULL);
    // calculate the time spend on the system() call
    t_duration = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
    t_duration += (t_end.tv_usec - t_start.tv_usec) / 1000.0;
    t_duration *= speed_factor;
    printf("\t\t%.3f ms elapsed\n\n", t_duration);

    // if (t_duration >= min && t_duration <= max) {
    //     fprintf(stdout, "Found Testcase for given time requirements.\n");
    //     return 0;
    // }
    
    // Test inverse sorted input:
    // see sorted input for clarification ...
    fprintf(stdout, "Testing inverse sorted input values:\n");
    out_file_ptr = fopen(out_file_name, "w");
    if (out_file_ptr == NULL) {
        fprintf(stderr, "ERROR Creating File!\n");
        return 4;
    }

    fprintf(out_file_ptr, "%lu\n", n);
    for (unsigned long j = n; j > 0; j--) {
        fprintf(out_file_ptr, "%lu\n", j);
    }

    fclose(out_file_ptr);
    gettimeofday(&t_start, NULL);

    if (system(cmd) > 0) {
        return 5;
    }

    gettimeofday(&t_end, NULL);
    t_duration = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
    t_duration += (t_end.tv_usec - t_start.tv_usec) / 1000.0;
    t_duration *= speed_factor;
    printf("\t\t%.3f ms elapsed\n\n", t_duration);

    // if (t_duration >= min && t_duration <= max) {
    //     fprintf(stdout, "Found Testcase for given time requirements.\n");
    //     return 0;
    // }
    
    // Test random input:
    fprintf(stdout, "Testing random input values:\n");
    for (int i = 0; i < amount_random_tries; i++) {
        out_file_ptr = fopen(out_file_name, "w");
        if (out_file_ptr == NULL) {
            fprintf(stderr, "ERROR Creating File!\n");
            return 6;
        }

        // generate new seed for new random values
        srand(time(NULL));

        // write n, and the n random values in the file
        // loop is copied from randnums.c
        fprintf(out_file_ptr, "%lu\n", n);
        for (unsigned long j = 0; j < n; j++) {
            int sign = (rand() % 2 == 0 ? 1 : -1);
            fprintf(out_file_ptr, "%d\n", sign * (rand() % 1000));
        }

        fclose(out_file_ptr);

        gettimeofday(&t_start, NULL);

        if (system(cmd) > 0) {
            return 7;
        }

        gettimeofday(&t_end, NULL);
        t_duration = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
        t_duration += (t_end.tv_usec - t_start.tv_usec) / 1000.0;
        t_duration *= speed_factor;
        printf("Iteration %d:\t%.3f ms elapsed\n", i+1, t_duration);

        // if we find a fitting testcase we simply exit the programm.
        // The file 'gentest.in' will then contain the working values
        if (t_duration >= min && t_duration <= max) {
            fprintf(stdout, "Found Testcase for given time requirements.\n");
            break;
        }
        if (i == amount_random_tries-1) {
            fprintf(stdout, "\nOptimal Testcase could not be found!\n");
        }
        
    }

    return 0;
}