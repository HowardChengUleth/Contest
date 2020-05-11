#include <stdio.h>

int main(void)
{
  int N, Q;
  int freq[10001];
  int accum[10001];
  int i, x;
  int case_num = 1;

  while (scanf("%d %d", &N, &Q) == 2 && (N || Q)) {
    for (i = 0; i <= 10000; i++) {
      freq[i] = 0;
    }
    for (i = 0; i < N; i++) {
      scanf("%d", &x);
      freq[x]++;
    }

    accum[0] = freq[0];
    for (i = 1; i <= 10000; i++) {
      accum[i] = accum[i-1] + freq[i];
    }

    printf("CASE# %d:\n", case_num++);
    for (i = 0; i < Q; i++) {
      scanf("%d", &x);
      if (!freq[x]) {
	printf("%d not found\n", x);
      } else if (!x) {
	printf("0 found at 1\n");
      } else {
	printf("%d found at %d\n", x, accum[x-1]+1);
      }
    }
  }
  return 0;
}
