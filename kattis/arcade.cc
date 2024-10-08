#include <bits/stdc++.h>

using namespace std;

int N;
int v[32*32];
int label[32][32];
int nbr[32*32][4];
double p[32*32][5];

const int dr[] = { -1, -1, 1, 1 };
const int dc[] = { -1, 0, 0, 1 };
  

void init()
{
  for (int i = 0; i < N; i++) {
    fill(label[i], label[i]+N, -1);
  }

  int curr = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < i+1; j++) {
      label[i][j] = curr++;
    }
  }

  for (int r = 0; r < N; r++) {
    for (int c = 0; c < r+1; c++) {
      for (int k = 0; k < 4; k++) {
	nbr[label[r][c]][k] = label[r + dr[k]][c + dc[k]];
      }
    }
  }
}


/*
 * Solution of systems of linear equations
 *
 * Author: Howard Cheng
 * Reference:
 *   K.E. Atkinson. "An Introduction to Numerical Analysis."  2nd Ed., John 
 *   Wiley & Sons, 1988, pages 520-521.  ISBN 0-471-62489-6
 *
 * To solve the system Ax = b where A is an n x n matrix, first call
 * LU_decomp on A to obtain its LU decomposition.  Once the LU
 * decomposition is obtained, it can be used to solve linear systems with
 * the same coefficient matrix A but different vectors of b using the
 * LU_solve routine.  This routine is numerically stable (provided that
 * the original coefficient matrix has a small condition number).
 *
 * The inputs to LU_decomp are the matrix A, the dimension n, an
 * output array pivot of n-1 elements such that pivot[i] = j means
 * that rows i and j were swapped during the i-th step, and an output
 * parameter to return the determinant of the matrix.  The function
 * returns 1 if successful, and 0 if the matrix is singular.  The
 * matrix A is overwritten by its LU decomposition on return.  If the
 * matrix is singular, the content of A should not be used (it represents
 * intermediate results during the decomposition).
 *
 * The inputs to LU_solve are the LU decomposition of A, the dimension
 * n, the pivot array from LU_decomp, and n-dimensional vectors b and
 * x.  This function should be called only if the original matrix A
 * has a small condition number.  You can check this by checking that
 * the determinant returned by LU_decomp is not too close to 0.  This is
 * only a crude check: you should really be computing the condition number
 * of the matrix.
 * 
 */

#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 32*32;

int LU_decomp(double A[MAX_N][MAX_N], int n, int pivot[], double &det)
{
  double s[MAX_N];           /* factors used in implicit scaling */
  double c, t;
  int i, j, k;

  det = 1.0;

  /* compute s[i] */
  for (i = 0; i < n; i++) {
    s[i] = 0.0;
    for (j = 0; j < n; j++) {
      if ((t = fabs(A[i][j])) > s[i]) {
	s[i] = t;
      }
    }
    if (s[i] == 0.0) {
      /* a row of zeroes: singular */
      det = 0.0;
      return 0;
    }
  }
  
  /* do the row reductions */
  for (k = 0; k < n-1; k++) {
    c = fabs(A[k][k]/s[k]);
    pivot[k] = k;
    for (i = k+1; i < n; i++) {
      t = fabs(A[i][k]/s[i]);
      if (t > c) {
	c = t;
	pivot[k] = i;
      }
    }

    if (c == 0) {
      /* pivot == 0: singular */
      det = 0.0;
      return 0;
    }

    /* do row exchange */
    if (k != pivot[k]) {
      det *= -1.0;
      for (j = k; j < n; j++) {
	t = A[k][j];
	A[k][j] = A[pivot[k]][j];
	A[pivot[k]][j] = t;
	t = s[k];
	s[k] = s[pivot[k]];
	s[pivot[k]] = t;
      }
    }

    /* do the row reduction */
    for (i = k+1; i < n; i++) {
      A[i][k] /= A[k][k];
      for (j = k+1; j < n; j++) {
	A[i][j] -= A[i][k] * A[k][j];
      }
    }

    det *= A[k][k];
  }
  
  /* note that the algorithm as state in the book is incorrect.  The */
  /* following is need to ensure that the last row is not all 0's.   */
  /* (maybe the book is correct, depending on what you think it's    */
  /* supposed to do.)                                                */
  if (A[n-1][n-1] == 0.0) {
    det = 0.0;
    return 0;
  } else {
    det *= A[n-1][n-1];
    return 1;
  }
}

void LU_solve(double A[MAX_N][MAX_N], int n, int pivot[], double b[], 
	      double x[])
{
  double t;
  int i, j, k;

  for (i = 0; i < n; i++) {
    x[i] = b[i];
  }
  for (k = 0; k < n-1; k++) {
    /* swap if necessary */
    if (k != pivot[k]) {
      t = x[k];
      x[k] = x[pivot[k]];
      x[pivot[k]] = t;
    }
    
    for (i = k+1; i < n; i++) {
      x[i] -= A[i][k] * x[k];
    }
  }

  x[n-1] /= A[n-1][n-1];
  
  for (i = n-2; i >= 0; i--) {
    for (j = i+1; j< n; j++) {
      x[i] -= A[i][j] * x[j];
    }
    x[i] /= A[i][i];
  }
}

double A[MAX_N][MAX_N], x[MAX_N], b[MAX_N];
int pivot[MAX_N];             /* only n-1 is needed, but what the heck */

void solve()
{
  int H = N*(N+1)/2;
  double det;

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < H; j++) {
      A[i][j] = 0;
    }
  }

  // E_i = expected value if we drop on hole i
  // E_i = p0 * E0 + p1 * E1 + p2 * E2 + p3 * E3 + p4 * val_i
  for (int i = 0; i < H; i++) {
    A[i][i] = 1;
    b[i] = p[i][4] * v[i];

    for (int j = 0; j < 4; j++) {
      if (p[i][j] > 0.0005) {
	A[i][nbr[i][j]] = -p[i][j];
      }
    }
  }

  if (LU_decomp(A, H, pivot, det)) {
    LU_solve(A, H, pivot, b, x);
    cout << fixed << setprecision(10) << x[0] << endl;
    return;
  }
  assert(false);
}



int main()
{
  cin >> N;

  int H = N*(N+1)/2;
  for (int i = 0; i < H; i++) {
    cin >> v[i];
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> p[i][j];
    }
  }
  
  init();
  
  solve();
  
  
  return 0;
}
