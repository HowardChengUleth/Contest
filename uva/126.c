/* @JUDGE_ID: 1102NT 126 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_DEG 200

typedef struct {
  int coeff[MAX_DEG+1][MAX_DEG+1];
  int max_xpow;
  int max_ypow;
} Poly;

void clear_poly(Poly *p)
{
  int i, j;
  for (i = 0; i <= MAX_DEG; i++) {
    for (j = 0; j <= MAX_DEG; j++) {
      p->coeff[i][j] = 0;
    }
  }
  p->max_xpow = p->max_ypow = 0;
}

int read_poly(Poly *p)
{
  char buffer[100];
  char *ptr;
  int sign, coeff, xpow, ypow;

  if (!fgets(buffer, 100, stdin) || buffer[0] == '#') {
    return 0;
  }

  ptr = buffer;
  if (*ptr == '-') {
    ptr++;
    sign = -1;
  } else {
    sign = 1;
  }

  while (!isspace(*ptr)) {
    coeff = (int)strtol(ptr, &ptr, 10);
    xpow = ypow = 0;
    while (*ptr == 'x' || *ptr == 'y') {
      if (*ptr == 'x') {
	ptr++;
	if (isdigit(*ptr)) { 
	  xpow = (int)strtol(ptr, &ptr, 10);
	} else {
	  xpow = 1;
	}
      } else if (*ptr == 'y') {
	ptr++;
	if (isdigit(*ptr)) {
	  ypow = (int)strtol(ptr, &ptr, 10);
	} else {
	  ypow = 1;
	}
      }
    }
    if (xpow > p->max_xpow) {
      p->max_xpow = xpow;
    }
    if (ypow > p->max_ypow) {
      p->max_ypow = ypow;
    }
    if (!coeff && (xpow || ypow)) {
      coeff = 1;
    }
    p->coeff[xpow][ypow] = sign * coeff;
    assert(*ptr == '+' || *ptr == '-' || isspace(*ptr));
    if (*ptr == '+') {
      sign = 1;
      ptr++;
    } else if (*ptr == '-') {
      sign = -1;
      ptr++;
    }
  }

  return 1;
}

void mult_poly(Poly *p, Poly *q, Poly *r)
{
  int i1, i2, j1, j2;

  for (i1 = 0; i1 <= p->max_xpow; i1++) {
    for (j1 = 0; j1 <= p->max_ypow; j1++) {
      if (p->coeff[i1][j1]) {
	for (i2 = 0; i2 <= q->max_xpow; i2++) {
	  for (j2 = 0; j2 <= q->max_ypow; j2++) {
	    r->coeff[i1+i2][j1+j2] += p->coeff[i1][j1] * q->coeff[i2][j2];
	    if (i1+i2 > r->max_xpow) {
	      r->max_xpow = i1+i2;
	    }
	    if (j1+j2 > r->max_ypow) {
	      r->max_ypow = j1+j2;
	    }
	  }
	}
      }
    }
  }
}

int print_term(char *line1, char *line2, int k, int coeff, int xpow, int ypow)
{
  char buffer[10];
  int i;

  /* print coefficient if necessary */
  assert(coeff > 0 && xpow >= 0 && ypow >= 0);
  if (coeff != 1 || (xpow == 0 && ypow == 0)) {
    sprintf(buffer, "%d", coeff);
    for (i = 0; i < strlen(buffer); i++) {
      line1[k] = ' ';
      line2[k] = buffer[i];
      k++;
    }
  }

  /* print power of x if necessary */
  if (xpow) {
    line1[k] = ' ';
    line2[k] = 'x';
    k++;
    if (xpow > 1) {
      sprintf(buffer, "%d", xpow);
      for (i = 0; i < strlen(buffer); i++) {
	line1[k] = buffer[i];
	line2[k] = ' ';
	k++;
      }
    }
  }

  /* print power of y if necessary */
  if (ypow) {
    line1[k] = ' ';
    line2[k] = 'y';
    k++;
    if (ypow > 1) {
      sprintf(buffer, "%d", ypow);
      for (i = 0; i < strlen(buffer); i++) {
	line1[k] = buffer[i];
	line2[k] = ' ';
	k++;
      }
    }
  }

  return k;
}

void print_poly(Poly *p)
{
  char line1[100], line2[100];
  int i, j, k, c;
  int first = 1;

  k = 0;
  for (i = p->max_xpow; i >= 0; i--) {
    for (j = 0; j <= p->max_ypow; j++) {
      c = p->coeff[i][j];
      if (c) {
	if (first) {
	  if (c > 0) {
	    k = print_term(line1, line2, k, c, i, j);
	  } else {
	    line1[k] = ' ';
	    line2[k] = '-';
	    k = print_term(line1, line2, k+1, -c, i, j);
	  }
	  first = 0;
	} else {
	  line1[k] = line1[k+1] = line1[k+2] = ' ';
	  line2[k] = line2[k+2] = ' ';
	  if (c > 0) {
	    line2[k+1] = '+';
	    k = print_term(line1, line2, k+3, c, i, j);
	  } else {
	    line2[k+1] = '-';
	    k = print_term(line1, line2, k+3, -c, i, j);
	  }
	}
      }
    }
  }
  line1[k] = line2[k] = 0;
  printf("%s\n%s\n", line1, line2);
}

int main(void)
{
  Poly p, q, r;
  int t;

  clear_poly(&p);
  clear_poly(&q);
  clear_poly(&r);
  while (read_poly(&p)) {
    t = read_poly(&q);
    assert(t);
    mult_poly(&p, &q, &r);
    print_poly(&r);
    clear_poly(&p);
    clear_poly(&q);
    clear_poly(&r);
  }
  return 0;
}
