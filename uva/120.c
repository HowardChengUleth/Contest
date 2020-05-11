#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_DISK 100

int max_index(int *stack, int n)
{
  int i;
  int best_i, best;

  if (n <= 0) {
    return 0;
  }
  best = stack[0];
  best_i = 0;
  for (i = 1; i < n; i++) {
    if (stack[i] >= best) {
      best = stack[i];
      best_i = i;
    }
  }
  return best_i;
}

void flip(int *stack, int n)
{
  int i, j, t;

  for (i = 0, j = n; i <= n/2; i++, j--) {
    t = stack[i];
    stack[i] = stack[j];
    stack[j] = t;
  }
}

void process(int *stack, int n)
{
  int i,j;
  int max_i;

  assert(n <= 30);
  for (i = n-1; i >= 0; i--) {
    max_i = max_index(stack, i+1);
    assert(max_i <= i);
    if (max_i < i) {
      if (max_i != 0) {
	flip(stack, max_i);
	printf("%d ", n-max_i);
	assert(max_index(stack, i+1) == 0);
      }
      flip(stack, i);
      printf("%d ", n-i);
    }
    assert(stack[max_index(stack, i+1)] == stack[i]);
  }

  printf("0 \n");
}

int main(void)
{
  int n;
  int stack[MAX_DISK];
  char buffer[10240];
  char *p;

  while (fgets(buffer, 10240, stdin)) {
    n = 0;
    p = strtok(buffer, " \n");
    stack[n++] = atoi(p);
    printf("%d", stack[n-1]);
    while ((p = strtok(NULL, " \n"))) {
      stack[n++] = atoi(p);
      printf(" %d", stack[n-1]);
    }
    printf(" \n");
    process(stack, n);
  }
  return 0;
}
