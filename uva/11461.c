#include <stdio.h>

char square[100001];
int num_square[100001];

int main(void)
{
  int i;
  int a, b;

  for (i = 0; i*i <= 100000; i++) {
    square[i*i] = 1;
  }
  num_square[0] = 1;
  for (i = 1; i <= 100000; i++) {
    num_square[i] = num_square[i-1] + square[i];
  }

  while (scanf("%d %d", &a, &b) == 2 && (a || b)) {
    printf("%d\n", num_square[b] - num_square[a-1]);
    
  }
  return 0;
}
