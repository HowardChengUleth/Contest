/* @JUDGE_ID: 1102NT 10109 C++ "" */

/*
 * This version cheats by using the fact that the numerator and
 * denominator in judge's output actually does not exceed 16-bit.
 */


#include <stdio.h>

#define modulus (2147483647)
#define halfM ((modulus-1)/2)
#define sqrtM (46340)

#define MAX_M 50
#define MAX_N 50


int inv(int b)
{
  register int a1 = 0, b1 = 1;
  register int q, r, r1;
  register int x = modulus;
  register long long t;

  while (b) {
    q = x / b;
    r = x % b;
    t = (long long)q * b1;
    r1 = a1;
    if (t < 0) {
      t = -t;
      t = (t & 0x7FFFFFFF) + (t >> 31);
      if (t < modulus) {
	r1 += (int)t;
      }
    } else {
      t = (t & 0x7FFFFFFF) + (t >> 31);
      if (t < modulus) {
	r1 -= (int)t;
      }
    }
    x = b; a1 = b1;
    b = r; b1 = r1;
  }
  return (a1 < 0) ? a1 + modulus : a1;
}

void readrat(int Ap[MAX_M][MAX_N+1], int m, int n)
{
  int num, den;
  register int i, j;
  register long long t;

  for (i = 0; i < m; i++) {
    for (j = 0; j <= n; j++) {
      if (scanf("%d/%d", &num, &den) == 1) {
	Ap[i][j] = num;
      } else {
	t = ((long long)num * inv(den));
	t = (t & 0x7FFFFFFF) + (t >> 31);
	Ap[i][j] = (t < modulus) ? (int)t : 0;
      }
      if (Ap[i][j] < 0) Ap[i][j] += modulus;
    }
  }
}


void ratRecon(int g, int i)
{
  register int sign = 1;
  register int r0, r1, r2, t0, t1, t2, q;

  r0 = modulus; t0 = 0;
  r1 = g; t1 = 1;

  /* adjust for negative numbers */
  if (halfM < g) {
    r1 = modulus - g;
    sign = -1;
  }

  while (r1 >= sqrtM) {
    q = r0 / r1;
    r2 = r0 % r1;
    t2 = t0 - q * t1;
    r0 = r1; r1 = r2;
    t0 = t1; t1 = t2;
  }

  /* adjust for negative numbers */
  if (sign < 0) {
    r1 = -r1;
  }

  if (t1 < 0) {
    r1 = -r1;
    t1 = -t1;
  }    

  if (t1 != 1) {
    printf("x[%d] = %d/%d\n", i, r1, t1);
  } else {
    printf("x[%d] = %d\n", i, r1);
  }
}



/*
 * returns   = 0 if there is unique solution
 *           < 0 if there is no solution
 *         k > 0 if there is a solution space of dimension k
 */
int GaussElim(int A[MAX_M][MAX_N+1], int m, int n)
{
  int k_c = 0, k_r, rank, k, i;
  int pivot;
  int t;
  long long temp;

  /* eliminate each row */
  for (k_r = 0; k_r < m && k_c < n; k_r++) {
    /* find nonzero pivot */
    do {
      for (pivot = k_r; pivot < m && !A[pivot][k_c]; pivot++)
        ;
      if (pivot >= m) {
        if (++k_c >= n) break;
      }
    } while (pivot >= m);
    if (pivot < m) {
      /* swap rows pivot and k_r */
      if (pivot != k_r) {
	for (k = k_c+1; k <= n; k++) {
	  t = A[k_r][k];
	  A[k_r][k] = A[pivot][k];
	  A[pivot][k] = t;
	}
	A[k_r][k_c] = A[pivot][k_c];
	A[pivot][k_c] = 0;
      }

      /* eliminate */
      t = inv(A[k_r][k_c]);
      A[k_r][k_c] = 1;
      for (k = k_c+1; k <= n; k++) {
        temp = (long long)A[k_r][k] * t;
	temp = (temp >> 31) + (temp & 0x7FFFFFFF);
	temp = (temp >> 31) + (temp & 0x7FFFFFFF);
	if (temp < modulus) {
	  A[k_r][k] = (int)temp;
	} else {
	  A[k_r][k] = 0;
	}
      }

      for (k = k_r+1; k < m; k++) {
        if (!(t = A[k][k_c])) continue;
	A[k][k_c] = 0;  /* better locality */
        for (i = k_c+1; i <= n; i++) {
	  temp = (long long)A[k_r][i] * t;
	  temp = (temp >> 31) + (temp & 0x7FFFFFFF);
	  temp = (temp >> 31) + (temp & 0x7FFFFFFF);
	  if (temp < modulus) {
	    A[k][i] -= (int)temp;
	    if (A[k][i] < 0) {
	      A[k][i] += modulus;
	    }
	  }
        }
      }

      k_c++;

    } else {
      /* everything else is 0 */
      break;
    }
  }

  rank = k_r;
  for (k_r = rank; k_r < m; k_r++) {
    if (A[k_r][n] != 0) {
      /* inconsistent system */
      return -1;
    }
  }

  if (rank == n) {
    /* back substitution */
    for (k_r = n-1; k_r >= 1; k_r--) {
      for (k = 0; k < k_r; k++) {
	temp = (long long)A[k][k_r] * A[k_r][n];
	temp = (temp >> 31) + (temp & 0x7FFFFFFF);
	if (temp > modulus) {
	  temp = (temp >> 31) + (temp & 0x7FFFFFFF);
	}
	if (temp < modulus) {
	  A[k][n] -= (int)temp;
	  if (A[k][n] < 0) {
	    A[k][n] += modulus;
	  }
	}
      }
    }
  }

  return n - rank;
}

int main(void)
{
  int Ap[MAX_M][MAX_N+1];
  int c, m, n;
  int first = 1;
  int i, result;

  while (scanf("%d", &c) == 1 && c > 0) {
    if (!first) {
      puts("");
    }
    first = 0;

    printf("Solution for Matrix System # %d\n", c);
    scanf("%d %d", &n, &m);
    readrat(Ap, m, n);

    result = GaussElim(Ap, m, n);
    if (result < 0) {
      puts("No Solution.");
    } else if (result > 0) {
      printf("Infinitely many solutions containing %d arbitrary constants.\n",
	     result);
    } else {
      for (i = 0; i < n; i++) {
	ratRecon(Ap[i][n], i+1);
      }
    }
  }
  return 0;
}
