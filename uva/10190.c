/* @JUDGE_ID: 1102NT 10190 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  int n, m;
  int a[100], i;

  while (scanf("%d %d", &n, &m) == 2) {
    if (m > n || m == 1 || m == 0 || n == 0) {
      printf("Boring!\n");
      continue;
    }
    a[0] = n;
    for (i = 0; a[i] != 1; i++) {
      a[i+1] = a[i] / m;
      if (a[i] % m != 0 || a[i+1] >= a[i]) {
	break;
      }
    }
    if (a[i] == 1) {
      for (i = 0; a[i] != 1; i++) {
	printf("%d ", a[i]);
      }
      printf("1\n");
    } else {
      printf("Boring!\n");
    }
  }
  return 0;

}
