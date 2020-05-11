#include <stdio.h>
#include <math.h>

void solve(int N)
{
  long long diag, denom, numer;

  diag = (long long)floor(ceil((-1 + sqrt(1 + 8*N))/2)+0.5);

  if (diag % 2 == 0) {
    denom = diag*(diag+1)/2 - N + 1;
    numer = diag+1 - denom;
  } else {
    numer = diag*(diag+1)/2 - N + 1;
    denom = diag+1 - numer;
  }
 
  printf("%lld/%lld\n", numer, denom);
}

int main(void)
{
  int N;

  while (scanf("%d", &N) == 1) {
    printf("TERM %d IS ", N);
    solve(N);
  }

  return 0;
}
