/* @JUDGE_ID: 1102NT 392 C "" */

#include <stdio.h>

int read_poly(int *coeffs)
{
  int i;
  for (i = 8; i >= 0; i--) {
    if (scanf("%d", coeffs+i) != 1) {
      return 0;
    }
  }
  return 1;
}

void print_term(int c, int k)
{
  if (k == 0) {
    printf("%d", c);
  } else {
    if (c == -1) {
      printf("-");
    } else if (c != 1) {
      printf("%d", c);
    }
    if (k > 1) {
      printf("x^%d", k);
    } else {
      printf("x");
    }
  }
}

int main(void)
{
  int coeffs[9];
  int i;

  while (read_poly(coeffs)) {
    /* look for leading term */
    for (i = 8; i >= 0 && coeffs[i] == 0; i--) ;

    /* zero polynomial */
    if (i < 0) {
      printf("0\n");
      continue;
    }

    /* print leading term */
    print_term(coeffs[i], i);

    /* print the rest */
    for (i--; i >= 0; i--) {
      if (coeffs[i] > 0) {
	printf(" + ");
      } else if (coeffs[i] < 0) {
	printf(" - ");
	coeffs[i] *= -1;
      }
      if (coeffs[i]) {
	print_term(coeffs[i], i);
      }
    }
    printf("\n");
  }
  return 0;
}
