/* @JUDGE_ID: 1102NT 725 C "" */

#include <stdio.h>
#include <string.h>

int denom[100001];
int num_denom;

int distinct(long long x, int digits)
{
  char present[10];
  int i;

  memset(present, 0, 10);
  for (i = 0; i < digits; i++) {
    if (present[x % 10]) {
      return 0;
    }
    present[x % 10] = 1;
    x /= 10;
  }
  return (x == 0);
}

void init(void)
{
  int i;
  for (i = 1234; i <= 100000; i++) {
    if (distinct(i, 5)) {
      denom[num_denom++] = i;
    }
  }
}

void solve(int N)
{
  int num, i;
  int count = 0;

  for (i = 0; i < num_denom; i++) {
    if ((num = denom[i] * N) >= 100000) {
      break;
    }
    if (distinct(denom[i] + 100000*(long long)num, 10)) {
      printf("%05d / %05d = %d\n", num, denom[i], N);
      count++;
    }
  }

  if (!count) {
    printf("There are no solutions for %d.\n", N);
  }

}

int main(void)
{
  int first = 1;
  int N;

  init();
  while (scanf("%d", &N) == 1 && N) {
    if (!first) {
      printf("\n");
    } else {
      first = 0;
    }
    solve(N);
  }

  return 0;
}

