#include <stdio.h>

int num_digit[10];  /* number of i-digit numbers */

int main(void)
{
  int i, j, N;
  int digits, sum;
  int num, d;

  num_digit[0] = 0;
  num_digit[1] = 9;
  for (i = 2; i <= 9; i++) {
    num_digit[i] = 1;
    for (j = 0; j < i; j++) {
      num_digit[i] *= 10;
    }
    num_digit[i]--;

    for (j = 0; j < i; j++) {
      num_digit[i] -= num_digit[j];
    }
  }

  while (scanf("%d", &N) == 1) {
    /* first figure out how many digit the "current number" has */

    digits = 1;
    sum = 0;
    while (sum + digits*num_digit[digits] < N) {
      sum += digits*num_digit[digits];
      digits++;
    }

    N -= sum;
    num = 1;
    for (i = 0; i < digits-1; i++) {
      num *= 10;
    }
    num += (N-1) / digits;
    d = (digits-1) - ((N-1) % digits);
    
    while (d-- > 0) {
      num /= 10;
    }
    printf("%d\n", num % 10);
    

  }
  return 0;
}
