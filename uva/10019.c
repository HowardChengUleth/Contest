#include <stdio.h>

int ones(int n)
{
  int sum = 0;
  while (n > 0) {
    if (n & 1) {
      sum++;
    }
    n >>= 1;
  }
  return sum;
}

int main(void)
{
  int M, N, b1, b2;

  scanf("%d", &N);
  while (N--) {
    scanf("%d", &M);
    b1 = ones(M);
    b2 = 0;
    while (M > 0) {
      b2 += ones(M % 10);
      M /= 10;
    }
    printf("%d %d\n", b1, b2);
  }
  return 0;
}
