#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 

#define A 5000000
#define B 100000
#define C 100
// const int A = 500000000; // How many doubles we're going to pre-generate
// const int B = 100000; // The value to divide randomly-generated ints...by...to produce doubles

double operand1[A];
double operand2[A];

int stop = 0;

void *thread1(void *vargp) 
{
  double d;
  int i = 0;
  int j = 0;

  while (j < C) {
    for (i = 0; i < A; i++) {
      d = operand1[i] * operand2[i];
      // d = operand1[i] / operand2[i];
      if (stop == 1)
        break;
    }

    if (stop == 1)
      break;
    j++;
  }

  if (stop == 0)
    printf("Finished! (%d)\n", A);
  else
    printf("%d\t%d\t%d\n", j, i, A*C);

  return NULL;
} 
   
int main() { 
  srand(getpid());

  // printf("Pre-generating\n");
  for (int i = 0; i < A; i++) {
    operand1[i] = rand() / (double)B; // arc4random() / (double)B;
    operand2[i] = rand() / (double)B; // arc4random() / (double)B;
  }
  // printf("Here we go!!\n");

  // printf("Ready\n");
  // for (int i = A -1; i > A-50; i--)
  //   printf("  %f\n", operand1[i]);

  pthread_t thread_id1; 
  pthread_create(&thread_id1, NULL, thread1, NULL);
  sleep(1);
  stop = 1; 
  // printf("Time!!\n");
  pthread_join(thread_id1, NULL); 

  exit(0); 
}
