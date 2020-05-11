#include <stdio.h>


void solve(int n)
{
  int s1, s2, s3;
  int best = 4*n+2;
  int area;

  for (s1 = 1; s1 <= n; s1++) {
    if (n % s1) continue;
    for (s2 = s1; s2 <= n; s2++) {
      if (n % (s1*s2)) continue;
      s3 = n/(s1*s2);
      area = 2*(s1*s2 + s2*s3+ s1*s3);
      if (area < best) {
	best = area;
      }
    }
  }
  
  printf("%d\n", best);
}

int main(void)
{
  int N, C;

  scanf("%d", &C);
  while (C-- > 0) {
    scanf("%d", &N);
    solve(N);
  }
  return 0;
}
