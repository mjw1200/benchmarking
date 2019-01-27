#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <sys/time.h>

const int A = 500000000; // How many doubles we're going to pre-generate
const int B = 100000; // The value to divide randomly-generated ints...by...to produce doubles

double operand1[A];
double operand2[A];

int stop = 0;

void *thread1(void *vargp) 
{
  double d;
  int i = 0;

  for (; i < A; i++) {
    d = operand1[i] * operand2[i];
    d = operand1[i] / operand2[i];
    if (stop == 1)
      break;
  }

  if (i == A)
    printf("Finished! (%d)\n", A);
  else
    printf("Got through %d of %d\n", i, A);

  return NULL;
} 
   
int main() { 
  printf("Pre-generating\n");
  for (int i = 0; i < A; i++) {
    operand1[i] = arc4random() / (double)B;
    operand2[i] = arc4random() / (double)B;
  }
  printf("Here we go!!\n");

  // printf("Ready\n");
  // for (int i = A -1; i > A-50; i--)
  //   printf("  %f\n", operand1[i]);

  pthread_t thread_id1; 
  pthread_create(&thread_id1, NULL, thread1, NULL);
  sleep(1);
  stop = 1; 
  printf("Time!!\n");
  pthread_join(thread_id1, NULL); 

  exit(0); 
}