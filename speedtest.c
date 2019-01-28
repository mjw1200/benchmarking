#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 

#define DIVIDENDS 500000
#define DIVISORS 50000
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

//-------------------------------------------------------------------------------------------------
// Divide as many big doubles as we can before we're told to stop
//-------------------------------------------------------------------------------------------------
void *thread(void *vargp) 
{
  uint64_t counter = 0;
  double result = 0.0;
  int i = 0;
  int j = 0;

  while (stop == 0) {
    for (i = 0; i < DIVISORS; i++) {
      for (j = 0; j < DIVIDENDS; j++) {
        // printf("%d\t%d\t%d\n", i, j, stop);
        result = dividends[j] / divisors[i];
        counter++;

        if (stop == 1)
          break;
      }

      if (stop == 1)
        break;
    }
  }

  printf("Did %llu divisions\n", counter);

  return NULL;
} 
   
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// main
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
int main() {
  srand(getpid());

  prePopulate();

  pthread_t thread_id1; 
  pthread_create(&thread_id1, NULL, thread, NULL);
  sleep(1);
  stop = 1; 
  pthread_join(thread_id1, NULL); 

  return 0;
}
