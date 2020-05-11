/* @JUDGE_ID: 1102NT 10370 C "" */

#include <stdio.h>

int main(void)
{
  int cases;
  int A[1000];
  int sum;
  double avg;
  int N, i, count;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d", &N);
    sum = 0;
    for (i = 0; i < N; i++) {
      scanf("%d", A+i);
      sum += A[i];
    }
    avg = (double)sum / N;
    count = 0;
    for (i = 0; i < N; i++) {
      if (A[i] > avg) {
	count++;
      }
    }
    printf("%.3f%%\n", (double)count*100/N);
  }
  return 0;
}
