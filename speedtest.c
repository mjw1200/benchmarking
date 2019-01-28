#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 

#define DIVIDENDS 500
#define DIVISORS 50
#define THREADS 2

double dividends[DIVIDENDS];
double divisors[DIVISORS];

pthread_t threadIDs[THREADS];

int stop = 0;

//-------------------------------------------------------------------------------------------------
// Generate a large-ish, random-ish double value
//-------------------------------------------------------------------------------------------------
double getBigDouble() {
  uint64_t rand1 = rand();
  uint64_t rand2 = rand();
  uint64_t bigRand = rand1 * rand2;
  double bigDouble = bigRand / 1e6;
  
  return bigDouble;
}

//-------------------------------------------------------------------------------------------------
// Pre-populate the dividend and divisor arrays
//-------------------------------------------------------------------------------------------------
void prePopulate() {
  int i = 0;

  printf("Generating dividends...\n");
  for (i = 0; i < DIVIDENDS; i++)
    dividends[i] = getBigDouble();

  printf("Generating divisors...\n");
  for (i = 0; i < DIVISORS; i++)
    divisors[i] = getBigDouble();
}

void *thread(void *vargp) 
{
  uint64_t counter = 0;
  double result = 0.0;
  int i = 0;
  int j = 0;

  while (stop == 0) {
    for (i = 0; i < DIVISORS; i++) {
      for (j = 0; j < DIVIDENDS; j++) {
        result = dividends[j] / divisors[i];
        // printf("%d\t%d\t%f\n", i, j, result);
        counter++;

        if (stop == 1)
          break;
      }

      if (stop == 1)
        break;
    }

    stop = 1;
  }

  printf("Did %llu divisions\n", counter);

  return NULL;
} 
   
int main() {
  srand(getpid());

  prePopulate();
  thread(NULL);

  return 0;
}

int smain() { 
  // srand(getpid());

  // // printf("Pre-generating\n");
  // for (int i = 0; i < A; i++) {
  //   operand1[i] = rand() / (double)B; // arc4random() / (double)B;
  //   operand2[i] = rand() / (double)B; // arc4random() / (double)B;
  // }
  // // printf("Here we go!!\n");

  // // printf("Ready\n");
  // // for (int i = A -1; i > A-50; i--)
  // //   printf("  %f\n", operand1[i]);

  // pthread_t thread_id1; 
  // pthread_create(&thread_id1, NULL, thread, NULL);
  // sleep(1);
  // stop = 1; 
  // // printf("Time!!\n");
  // pthread_join(thread_id1, NULL); 

  return(0); 
}
