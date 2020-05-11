/* @JUDGE_ID: 1102NT 533 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void expr(char *buffer, int *x_coeff, int *c_coeff);

void factor(char *buffer, int *x_coeff, int *c_coeff)
{
  int len = strlen(buffer);
  char buf[1000];
  int i;
  if (buffer[0] == 'x') {
    assert(len == 1);
    *x_coeff = 1;
    *c_coeff = 0;
  } else if (buffer[0] == '(') {
    assert(buffer[len-1] == ')');
    for (i = 0; i < len-2; i++) {
      buf[i] = buffer[i+1];
    }
    buf[i] = 0;
    expr(buf, x_coeff, c_coeff);
  } else {
    *x_coeff = 0;
    *c_coeff = atoi(buffer);
  }

}

void term(char *buffer, int *x_coeff, int *c_coeff)
{
  int i, found, x_1, x_2, c_1, c_2, j;
  char buf[1000];
  int brackets = 0;
 
  /* find first * */
  found = 0;
  for (i = 0; buffer[i] && !found; i++) {
    if (buffer[i] == '(') {
      brackets++;
    } else if (buffer[i] == ')') {
      brackets--;
    } else if (buffer[i] == '*' && !brackets) {
      found = 1;
    }
  }
  if (!found) {
    factor(buffer, x_coeff, c_coeff);
  } else {
    i--;
    for (j = 0; j < i; j++) {
      buf[j] = buffer[j];
    }
    buf[j] = 0;
    factor(buf, &x_1, &c_1);

    term(buffer+i+1, &x_2, &c_2);
    
    /* do later */
    assert(!(x_1 && x_2));
    *x_coeff = x_1 * c_2 + x_2 * c_1;
    *c_coeff = c_1 * c_2;
  }
}

void expr(char *buffer, int *x_coeff, int *c_coeff)
{
  int i, found, t_x, t_y, j;
  char buf[1000];
  int brackets = 0;
  int sign;

  /* find first + or - */
  found = 0;
  for (i = 0; buffer[i] && !found; i++) {
    if (buffer[i] == '(') {
      brackets++;
    } else if (buffer[i] == ')') {
      brackets--;
    } else if (!brackets && (buffer[i] == '+' || buffer[i] == '-')) {
      found = 1;
      sign = (buffer[i] == '+') ? 1 : -1;
    }
  }
  if (!found) {
    term(buffer, x_coeff, c_coeff);
  } else {
    i--;
    for (j = 0; j < i; j++) {
      buf[j] = buffer[j];
    }
    buf[j] = 0;
    term(buf, x_coeff, c_coeff);
    expr(buffer+i+1, &t_x, &t_y);
    *x_coeff += sign*t_x;
    *c_coeff += sign*t_y;
  }
}

void solve_eqn(char *buffer)
{
  char buf1[1000], buf2[1000];
  char *p1, *p2;
  int i, len;
  int l_x, r_x, l_c, r_c;
  double x;

  p1 = strchr(buffer, '=');
  len = strlen(buffer);

  for (i = 0, p2 = buffer; p2 != p1; p2++, i++) {
    buf1[i] = *p2;
  }
  buf1[i] = 0;

  for (i = 0, p2 = p1+1; *p2; p2++, i++) {
    buf2[i] = *p2;
  }
  buf2[i] = 0;

  expr(buf1, &l_x, &l_c);
  expr(buf2, &r_x, &r_c);

  if (l_x == r_x) {
    if (l_c == r_c) {
      printf("Infinitely many solutions.\n");
    } else {
      printf("No solution.\n");
    }
  } else {
    x =  (double)(r_c - l_c) / (double)(l_x - r_x);
    printf("x = %.6f\n", x);
  }
}

int main(void)
{
  char buffer[1000];
  int case_no = 1;

  while (scanf("%s", buffer) == 1) {
    if (case_no > 1) {
      printf("\n");
    }
    printf("Equation #%d\n", case_no++);
    solve_eqn(buffer);
  }
  return 0;

}
