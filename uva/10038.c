/* @JUDGE_ID: 1102NT 10038 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  char diff[3000];
  int i, prev, next, n, d;

  while (scanf("%d", &n) == 1) {
    for (i = 0; i < 3000; i++) {
      diff[i] = 0;
    }
    scanf("%d", &prev);
    for (i = 1; i < n; i++) {
      scanf("%d", &next);
      d = (prev > next) ? prev - next : next - prev;
      if (1 <= d && d < n) {
	diff[d] = 1;
      }
      prev = next;
    }
    for (i = 1; i < n; i++) {
      if (!diff[i]) {
	printf("Not jolly\n");
	break;
      }
    }
    if (i >= n) {
      printf("Jolly\n");
    }
  }

  return 0;
}
