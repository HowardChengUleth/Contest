#include <stdio.h>

void solve(int N)
{
  int f;
  int sum = (N > 1) ? 1 : 0;

  for (f = 2; f*f < N; f++) {
    if (N % f == 0) {
      sum += f + N/f;
    }
  }
  if (f*f == N) {
    sum += f;
  }
  if (sum == N) {
    printf("PERFECT\n");
  } else if (sum < N) {
    printf("DEFICIENT\n");
  } else {
    printf("ABUNDANT\n");
  }

}

int main(void)
{
  int N;

  printf("PERFECTION OUTPUT\n");
  while (scanf("%d", &N) == 1 && N) {
    printf("%5d  ", N);
    solve(N);
  }

  printf("END OF OUTPUT\n");
  return 0;
}
