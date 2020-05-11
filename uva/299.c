/* @JUDGE_ID: 1102NT 299 C "" */

#include <stdio.h>

int main(void)
{
  int N, L;
  int seq[50];
  int i, j;
  int inv;

  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d", &L);
    for (i = 0; i < L; i++) {
      scanf("%d", seq + i);
    }
    inv = 0;
    for (i = 0; i < L; i++) {
      for (j = i+1; j < L; j++) {
	if (seq[i] > seq[j]) inv++;
      }
    }
    printf("Optimal train swapping takes %d swaps.\n", inv);
  }
  return 0;
}
