/*
 *  Copyright (c) 2018-2020, Carnegie Mellon University
 *  See LICENSE for details
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "errcodes.h"
#include "opt_macros.h"


extern void INITFUNC(void);

#if (ALLOCATE_MEMORY)
extern void FUNC(double *Y, double *X);
#define RUN_FUNC FUNC(out, in)
#else
extern void FUNC(void);
#define RUN_FUNC FUNC()
#endif


// minimum number of total usecs for the main timing loop
#define REQUIRED_NSECS         1E8

// minimum number of times to call measured function in main timing loop
#define MIN_NUM_RUNS 1
#define MAX_NUM_RUNS 100000

// number of times to run the main timing loop
#define NUM_MAIN_LOOPS 2


vector_t * Input;
vector_t * Output;
vector_t * OutputCopy;


void initialize(int argc, char **argv) {
	unsigned long rows, cols, page, outsz;
	scalar_type_t *typ;

	sys_set_progname(argv[0]);
	srand(time(0));

	typ = scalar_find_type(DATATYPE);
	if (typ == NULL) {
		sys_fatal(EXIT_CMDLINE, "Error: datatype " DATATYPE " not found");
	}

	page = PAGESIZE;

#if (ALLOCATE_MEMORY)
	rows = ROWS;
	cols = COLUMNS;
#else
	rows = 1;
	cols = 1;
#endif
	outsz = 2 * rows + 1 + (page / typ->size);
	Output = vector_create_random(typ, outsz);
	OutputCopy = vector_create(typ, outsz);
	vector_copy(OutputCopy, Output);
	Input = vector_create_zero(typ, cols + 1 + (page / typ->size));

	INITFUNC();
}

// return elapsed time from start to end
double time_in_nanosec(struct timespec start, struct timespec end) {
    double time;
    if (end.tv_nsec < start.tv_nsec) {
        time = (double)(end.tv_nsec + 1000000000 - start.tv_nsec);
        time += (double)((end.tv_sec - start.tv_sec - 1) * 1000000000);
    } else {
        time = (double)(end.tv_nsec - start.tv_nsec);
        time += (double)((end.tv_sec - start.tv_sec) * 1000000000);
    }
    return time;
}

double perform_timing() {
	struct timespec start_nsecs, end_nsecs;
	double count, min_count;
	int run, i;
	int num_runs = MIN_NUM_RUNS;

#if (ALLOCATE_MEMORY)
	static void *in, *out;
	out = Output->data;
	in = Input->data;
#endif

	// make sure function runs enough times to get a minimum total usec count
	while (num_runs <= MAX_NUM_RUNS)
	{
		clock_gettime(CLOCK_MONOTONIC, &start_nsecs);
		for (run = 0; run < num_runs; ++run) {
			RUN_FUNC;
		}
		clock_gettime(CLOCK_MONOTONIC, &end_nsecs);
		//fprintf(stderr, "Runs: %d, usecs: %lld\n", num_runs,
		//	end_usecs - start_usecs);

		if (time_in_nanosec(start_nsecs, end_nsecs) >= REQUIRED_NSECS) break;

		num_runs *= 10;
	}

	/* start of measurement */

	min_count = 0;
	for (i = 0; i < NUM_MAIN_LOOPS; i++)
	{
	  //fprintf(stderr, "\nOUTER LOOP %d\n", i+1);

		clock_gettime(CLOCK_MONOTONIC, &start_nsecs);
		for (run = 0; run < num_runs; ++run) {
			RUN_FUNC;
		}
		clock_gettime(CLOCK_MONOTONIC, &end_nsecs);

		//fprintf(stderr, "start %lld, end %lld\n", start_usecs, end_usecs);

		count = time_in_nanosec(start_nsecs, end_nsecs);

		//fprintf(stderr, "count %lld\n", count);

		if ((min_count <= 0) || (count < min_count)) {
			min_count = count;
		}

		//fprintf(stderr, "min_count %lld, num_runs %d\n", min_count, num_runs);


	}
	return ((double)min_count / num_runs);
}


int main(int argc, char** argv) {
	double nsecs;
#if (ALLOCATE_MEMORY)
	void *out, *in;
#endif

	initialize(argc, argv);

#if (ALLOCATE_MEMORY)
	out = Output->data;
	in = Input->data;
	Output->data = out;
#endif

	nsecs = perform_timing();

	printf("%e;\n", nsecs);

	return EXIT_SUCCESS;
}
