#ifndef MMM_H_
#define MMM_H_

// global thread variables
extern double **input1;
extern double **input2;
extern double **output;
extern double **tempoutput;
extern int size;

struct threadArgs {
    double startRow; 
    double endRow; 
};

void mmm_init();
void mmm_reset(double **);
void mmm_freeup();
void mmm_seq();
void *mmm_par(void *args);
double mmm_verify();
void printMatrix(double **matrix);
void copyOutput();

#endif /* MMM_H_ */