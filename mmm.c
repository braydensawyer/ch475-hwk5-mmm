#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "mmm.h"

double **input1;
double **input2;
double **output;
double **tempoutput;

/**
 * Allocate and initialize the matrices on the heap. Populate
 * the input matrices with random numbers from 0 to 99
 */
void mmm_init() {
	// TODO
	// first array
	input1 = (double **) malloc(size * sizeof(double*));
	for (int i = 0; i < size; i++) {
		input1[i] = (double*) malloc(sizeof(double) * size);
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			input1[i][j] = rand() % 100;
		}
	}
	// second array
	input2 = (double **) malloc(size * sizeof(double*));
	for (int i = 0; i < size; i++) {
		input2[i] = (double*) malloc(sizeof(double) * size);
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			input2[i][j] = rand() % 100;
		}
	}
	// output array
	output = (double**) malloc(sizeof(double*) * size);
	for (int i = 0; i < size; i++) {
		output[i] = (double*) malloc(sizeof(double) * size);
	}
	// temp output array
	tempoutput = (double**) malloc(sizeof(double*) * size);
	for (int i = 0; i < size; i++) {
		tempoutput[i] = (double*) malloc(sizeof(double) * size);
	}

	// TODO
	srand((unsigned)time(NULL));

}

/**
 * Reset a given matrix to zeroes (their size is in the global var)
 * @param matrix pointer to a 2D array
 */
void mmm_reset(double **matrix) {
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			matrix[i][j] = 0;
		}
	}
}

/**
 * Free up memory allocated to all matrices
 * (their size is in the global var)
 */
void mmm_freeup() {
	// free input1
	for (int i = 0; i < size; i++) {
		free(input1[i]);
		input1[i] = NULL;  // remove dangling pointer
	}
	free(input1);
	input1 = NULL;  //remove dangling pointer
	// free input2
	for (int i = 0; i < size; i++) {
		free(input2[i]);
		input2[i] = NULL;  // remove dangling pointer
	}
	free(input2);
	input2 = NULL;  //remove dangling pointer
	// free output
	for (int i = 0; i < size; i++) {
		free(output[i]);
		output[i] = NULL;  // remove dangling pointer
	}
	free(output);
	output = NULL;  //remove dangling pointer
	// free tempoutput
	for (int i = 0; i < size; i++) {
		free(tempoutput[i]);
		tempoutput[i] = NULL;  // remove dangling pointer
	}
	free(tempoutput);
	tempoutput = NULL;  //remove dangling pointer
}

/**
 * Sequential MMM (size is in the global var)
 */
void mmm_seq() {
	// TODO - code to perform sequential MMM
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			for(int k = 0; k < size; k++){
				output[i][j] += input1[i][k] * input2[k][j];
			}
		}
	}
}

/**
 * Parallel MMM
 */
void *mmm_par(void *args) {
	// TODO - code to perform parallel MMM
	struct threadArgs *tArgs = (struct threadArgs *) args;
	double startRow = tArgs->startRow;
    double endRow = tArgs->endRow;
	for (int i = startRow; i <= endRow; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                output[i][j] += input1[i][k] * input2[k][j];
            }
        }
    }
	return NULL;
}


/**
 * Verifies the correctness between the matrices generated by
 * the sequential run and the parallel run.
 *
 * @return the largest error between two corresponding elements
 * in the result matrices
 */
double mmm_verify() {
	// TODO
	double error = 0.0; 
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(abs(output[i][j] - tempoutput[i][j]) > error){
				error = abs(output[i][j] - tempoutput[i][j]);
			}
		}
	}
	return error;
}

//prints a given matrix
void printMatrix(double **matrix){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

//copies output matrix to the tempout matrix
void copyOutput(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			tempoutput[i][j] = output[i][j];
		}
	}
}
