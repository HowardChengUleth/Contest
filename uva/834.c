/* @JUDGE_ID: 1102NT 834 C "" */

#include <stdio.h>

int main(void)
{
  int a, b, r;
  int first;
  int adj;

  while (scanf("%d %d", &a, &b) == 2) {

    /* worry about negative numbers */
    adj = 0;
    if (a < 0 && b < 0) {
      a *= -1;
      b *= -1;
    } else if (a < 0 || b < 0) {
      if (b < 0) {
	a *= -1;
	b *= -1;
      }
      while (a < 0) {
	adj++;
	a += b;
      }
    } 

    printf("[");
    printf("%d", a/b - adj);
    r = a % b;
    a = b;
    b = r;
    first = 1;
    while (b) {
      if (first) {
	printf(";");
      } else {
	printf(",");
      }
      r = a % b;
      printf("%d", a/b);
      first = 0;
      a = b;
      b = r;
    }
    printf("]\n");
  }
  return 0;
}
