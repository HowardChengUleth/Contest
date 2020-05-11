#include <stdio.h>

int main(void)
{
  int N;
  int internal;
  int num1, num2;

  while (scanf("%d", &N) == 1) {
    /* no borrowing */
    internal = (N-1)/2;
    num1 = 3*internal+1 + (N-1)%2;

    /* borrow 1 bottle */
    internal = N/2;
    num2 = 3*internal + N%2;
    
    printf("%d\n", ((num1 > num2) ? num1 : num2));
  }

  return 0;
}
