/* @JUDGE_ID: 1102NT 711 C "" */

/*
 * assign the number of each type of marbles each person get as a variable
 * (12 in total) and apply integer programming.
 *
 */

/*
 * All-integer programming
 *
 * Author: Howard Cheng
 * Reference:
 *   http://www.cs.sunysb.edu/~algorith/implement/syslo/distrib/processed/
 *
 * This algorithm is based on GOMORY cutting plane method.
 *                  
 * This algorithm solves the following INTEGER LP problem:
 *
 * minimize       SUM  (A[0][j] * x[j])         [cost function]
 *            (j=0 to n-1) 
 *
 *     s.t.       SUM   (a[i][j]*x[j])  <=  a[i][n+1]    1 <= i <= m
 *            (j=0 to n-1)
 *
 *     and        x[j] >= 0         0 <= j <= n-1
 *
 * n = number of variables
 * m = number of constraints
 *
 * Input : An input array A with m+n+1 rows and n+1 columns.
 *         Store the cost function in row 0, and the constraints in rows
 *           1 to m.  Set A[0][n] = 0.
 *         A vector x allocated for n values to store returned value.
 *
 * Output: Returns 1 if a solution is found, 0 if no solution exists.
 *         The minimum value of the cost function is returned in 
 *           value.
 *         The variable assignment to x[j] that gives the minimum is given 
 *           in x[j], where 0 <= j <= n-1.
 *
 * Important Notes:
 *
 * 1. If we want to have constraints that are >=, just multiply all the
 *    coefficients by -1.
 * 2. If we want to have constraints that are ==, do both >= and <=.
 * 3. The contents of A is destroyed after this routine.
 *
 */

#include <stdio.h>
#include <assert.h>


#define MAX_VARS  12
#define MAX_CONS  14
#define MAX_ROWS  MAX_VARS+MAX_CONS+1
#define MAX_COLS  MAX_VARS+1

int euclid(int u, int v)
{
  int w = u / v;
  if (w*v > u) {
    w--;
  }
  if ((w+1)*v <= u) {
    w++;
  }
  return w;
}

int int_prog(int A[MAX_ROWS][MAX_COLS], int n, int m, int *value, int *x)
{
  int iter, nosol;
  int b, c, i, j, k, l, r, r1, s, t, denom, num;

  /* set constraints that x[j] >= 0, and clear output */
  for (i = 0; i < n; i++) {
    for (j = 0; j < n+1; j++) {
      A[m+1+i][j] = 0;
    }
    A[m+1+i][i] = -1;
  }
  A[0][n] = 0;

  nosol = 0;
  do {
    r = 0;
    do {
      iter = (A[++r][n] < 0);
    } while (!iter && r != n+m);
    if (iter) {
      for (k = iter = 0; k < n && !iter; k++) {
	iter = (A[r][k] < 0);
      }
      nosol = !iter;
      if (iter) {
	l = k-1;
	for (j = k; j < n; j++) {
	  if (A[r][j] < 0) {
	    for (i = 0; !(s = A[i][j] - A[i][l]); i++)
	      ;
	    if (s < 0) {
	      l = j;
	    }
	  }
	}
	for (s = 0; !A[s][l]; s++)
	  ;
	num = -A[r][l];
	denom = 1;
	for (j = 0; j < n; j++) {
	  if (A[r][j] < 0 && j != l) {
	    for (i = s-1, b = 1; b && i >= 0; i--) {
	      b = (A[i][j] == 0);
	    }
	    if (b) {
	      i = A[s][j];
	      r1 = A[s][l];
	      t = euclid(i, r1);
	      if (t*r1 == i && t > 1) {
		for (i = s+1; !(r1 = t*A[i][l] - A[i][j]); i++)
		  ;
		if (r1 > 0) {
		  t--;
		}
	      }
	      c = -A[r][j];
	      if (c*denom > t*num) {
		num = c;
		denom = t;
	      }
	    }
	  }
	}
	for (j = 0; j <= n; j++) {
	  if (j != l) {
	    c = euclid(A[r][j]*denom, num);
	    if (c) {
	      for (i = 0; i <= n+m; i++) {
		A[i][j] += c*A[i][l];
	      }
	    }
	  }
	}
      }
    }
  } while (iter && !nosol);

  *value = -A[0][n];
  for (j = 0; j < n; j++) {
    x[j] = A[m+1+j][n];
  }

  return !nosol;
}

int marbles[6];

int read_case(void)
{
  int i;
  int more = 0;

  for (i = 0; i < 6; i++) {
    scanf("%d", marbles+i);
    if (marbles[i]) {
      more = 1;
    }
  }
  return more;
}

int main(void)
{
  int A[MAX_ROWS][MAX_COLS];
  int x[MAX_VARS];
  int val;
  int i, j;
  int case_num = 1;

  while (read_case()) {
    /* dummy cost function */
    for (i = 0; i < 12; i++) {
      A[0][i] = 1;
    }
    A[0][12] = 0;

    /* set constraints */
    for (i = 0; i < 6; i++) {
      for (j = 0; j < 12; j++) {
	A[2*i+1][j] = A[2*i+2][j] = 0;
      }
      A[2*i+1][2*i] = A[2*i+1][2*i+1] = 1;  A[2*i+1][12] = marbles[i];
      A[2*i+2][2*i] = A[2*i+2][2*i+1] = -1; A[2*i+2][12] = -marbles[i];
    }
    for (i = 0; i < 6; i++) {
      A[13][2*i] = A[14][2*i+1] = i+1;    A[13][12] = 0;
      A[14][2*i] = A[13][2*i+1] = -(i+1); A[14][12] = 0;
    }

    printf("Collection #%d:\n", case_num++);
    if (int_prog(A, 12, 14, &val, x)) {
      printf("Can be divided.\n\n");
    } else {
      printf("Can't be divided.\n\n");
    }
  }

  return 0;
}

