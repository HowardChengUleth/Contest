#include <stdio.h>

int f[101];

int f91(int N)
{
  if (N >= 101) {
    return N - 10;
  } else if (f[N] >= 0) {
    return f[N];
  } else {
    return f[N] = f91(f91(N+11));
  }
}

int main(void)
{
  int N;
  int i;

  for (i = 0; i <= 100; i++) {
    f[i] = -1;
  }
  
  while (scanf("%d", &N) == 1 && N) {
    printf("f91(%d) = %d\n", N, f91(N));
  }

  return 0;
}
