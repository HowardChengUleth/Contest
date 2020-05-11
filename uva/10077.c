/* @JUDGE_ID: 1102NT 10077 C "" */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int m, n, lm, ln, rm, rn, cm, cn;

  while (scanf("%d %d", &m, &n) == 2 && !(m == 1 && n == 1)) {
    lm = 0; ln = 1;
    rm = 1; rn = 0;
    cm = 1; cn = 1;
    while (cm != m || cn != n) {
      if (m*cn < n*cm) {
	putchar('L');
	rm = cm; rn = cn;
	cm += lm; cn += ln;
      } else {
	putchar('R');
	lm = cm; ln = cn;
	cm += rm; cn += rn;
      }
    }
    printf("\n");
  }
  return 0;
}
