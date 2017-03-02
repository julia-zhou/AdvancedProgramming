#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

// Write array of number of iterations to file
// #define WRITE_RESULT

// Array dimensions
#define DIM 1000
#define DONE DIM*DIM

// Maximum number of iterations
#define MAX_ITER 10000

// Domain boundaries
#define XMIN -2
#define XMAX 1
#define YMIN -1.5
#define YMAX 1.5

// Complex number
typedef struct complex_{
  double real;
  double imag;
} Complex;

double mandelbrot_serial();
double mandelbrot_omp_d();

double mandelbrot_omp_s();

int main(int argc, char **argv){

  double time, time_d, time_s;
  time = mandelbrot_serial();
  time_d = mandelbrot_omp_d();
  time_s = mandelbrot_omp_d();
  printf("Serial version took %f seconds.\n",time);
  printf("Dynamic omp version took %f seconds.\n",time_d);
  printf("Static omp version took %f seconds.\n",time_s);
  return 0;
}

double mandelbrot_omp_s()
{
    /* Fill in your code here */
  int px, py, iter, ldim, *U, i=0, start, end;
  double tmp;
  Complex c, z;
  FILE *f;

  // Allocate global array to collect data 
  U = malloc(DIM*DIM*sizeof(int));

  start = 0;
  end = DIM*DIM-1;

  double tick = omp_get_wtime();
  #pragma omp parallel for private(px,py) num_threads(4) schedule(static)
  for(px=start/DIM; px<=end/DIM; px++){
    //#pragma omp parallel for private (py) num_threads(x) schedule(dynamic)
      for(py=0; py<DIM; py++){
          if((px==start/DIM) && (py==0)) py=start%DIM;
          if((px==end/DIM) && (py>end % DIM)) break;
          c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
          c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
          z.real = 0;
          z.imag = 0;
          iter = 0;
          while(z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
              tmp = z.real*z.real - z.imag*z.imag + c.real;
              z.imag = 2*z.real*z.imag + c.imag;
              z.real = tmp;
              iter++;
          }
          U[i] = iter;
          i++;
      }
  }
  double tock = omp_get_wtime();

  // Write DIM*DIM array of number of iterations at each point to file
  #ifdef WRITE_RESULT
  if((f = fopen("results_d.txt", "w")) == NULL){
      printf("Error opening file for writing.\n");
      exit(1);
  }
  for(py=0; py<DIM; py++){
      for(px=0; px<DIM; px++){
          fprintf(f, "%d ", U[DIM*px + py]);
      }
      fprintf(f, "\n");
  }
  fclose(f);
  #endif

  return tock-tick; 
    return 0;
}



double mandelbrot_omp_d()
{
    /* Fill in your code here */
  int px, py, iter, ldim, *U, i=0, start, end;
  double tmp;
  Complex c, z;
  FILE *f;

  // Allocate global array to collect data 
  U = malloc(DIM*DIM*sizeof(int));

  start = 0;
  end = DIM*DIM-1;

  double tick = omp_get_wtime();
  #pragma omp parallel for private(px,py) num_threads(4) schedule(dynamic)
  for(px=start/DIM; px<=end/DIM; px++){
    //#pragma omp parallel for private (py) num_threads(x) schedule(dynamic)
      for(py=0; py<DIM; py++){
          if((px==start/DIM) && (py==0)) py=start%DIM;
          if((px==end/DIM) && (py>end % DIM)) break;
          c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
          c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
          z.real = 0;
          z.imag = 0;
          iter = 0;
          while(z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
              tmp = z.real*z.real - z.imag*z.imag + c.real;
              z.imag = 2*z.real*z.imag + c.imag;
              z.real = tmp;
              iter++;
          }
          U[i] = iter;
          i++;
      }
  }
  double tock = omp_get_wtime();

  // Write DIM*DIM array of number of iterations at each point to file
  #ifdef WRITE_RESULT
  if((f = fopen("results_d.txt", "w")) == NULL){
      printf("Error opening file for writing.\n");
      exit(1);
  }
  for(py=0; py<DIM; py++){
      for(px=0; px<DIM; px++){
          fprintf(f, "%d ", U[DIM*px + py]);
      }
      fprintf(f, "\n");
  }
  fclose(f);
  #endif

  return tock-tick; 
    return 0;
}

double mandelbrot_serial()
{

  int px, py, iter, ldim, *U, i=0, start, end;
  double tmp;
  Complex c, z;
  FILE *f;

  // Allocate global array to collect data 
  U = malloc(DIM*DIM*sizeof(int));

  start = 0;
  end = DIM*DIM-1;

  double tick = omp_get_wtime();
  for(px=start/DIM; px<=end/DIM; px++){
      for(py=0; py<DIM; py++){
          if((px==start/DIM) && (py==0)) py=start%DIM;
          if((px==end/DIM) && (py>end % DIM)) break;
          c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
          c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
          z.real = 0;
          z.imag = 0;
          iter = 0;
          while(z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
              tmp = z.real*z.real - z.imag*z.imag + c.real;
              z.imag = 2*z.real*z.imag + c.imag;
              z.real = tmp;
              iter++;
          }
          U[i] = iter;
          i++;
      }
  }
  double tock = omp_get_wtime();

  // Write DIM*DIM array of number of iterations at each point to file
  #ifdef WRITE_RESULT
  if((f = fopen("results.txt", "w")) == NULL){
      printf("Error opening file for writing.\n");
      exit(1);
  }
  for(py=0; py<DIM; py++){
      for(px=0; px<DIM; px++){
          fprintf(f, "%d ", U[DIM*px + py]);
      }
      fprintf(f, "\n");
  }
  fclose(f);
  #endif

  return tock-tick; 
}
