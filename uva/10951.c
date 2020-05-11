/*
 * This is O(n^3) reduction of the Sylvester matrix...O(n^2) can be
 * achieved with Euclidean algorithm.
 *
 */

#include <stdio.h>
#include <assert.h>

int gcd(int a, int b, int *s)
{
  int r, r1, a1, b1, q;

  a1 = 1;
  b1 = 0;

  while (b) {
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    a = b;
    a1 = b1;
    b = r;
    b1 = r1;
  }

  *s = a1;
  return a;
}

int inv(int x, int m)
{
  int s;
  gcd(x, m, &s);
  if (s < 0) {
    return s+m;
  }
  if (s >= m) {
    return s-m;
  }
  return s;
}

int read_poly(int *poly, int p)
{
  int d;
  int i;

  scanf("%d", &d);
  for (i = d; i >= 0; i--) {
    scanf("%d", poly+i);
    poly[i] %= p;
  }
  return d;
}

void form_syl(int S[200][200], int n1, int *poly1, int n2, int *poly2)
{
  int i, j;
  int n = n1+n2;

  for (i = 0; i < n2; i++) {
    for (j = 0; j < i; j++) {
      S[i][j] = 0;
    }
    for (j = 0; j <= n1; j++) {
      S[i][i+j] = poly1[n1-j];
    }
    for (j = i+n1+1; j < n; j++) {
      S[i][j] = 0;
    }
  }
  for (i = 0; i < n1; i++) {
    for (j = 0; j < i; j++) {
      S[i+n2][j] = 0;
    }
    for (j = 0; j <= n2; j++) {
      S[i+n2][i+j] = poly2[n2-j];
    }
    for (j = i+n2+1; j < n; j++) {
      S[i+n2][j] = 0;
    }
  }
}

int reduce(int S[200][200], int n, int p)
{
  int i, j, k, t;
  int rank = 0;
  int c;

  for (k = 0; k < n; k++) {
    for (i = k; i < n && !S[i][k]; i++)
      ;
    if (i >= n) break;
    rank++;
    if (i != k) {
      for (j = k; j < n; j++) {
	t = S[i][j];
	S[i][j] = S[k][j];
	S[k][j] = t;
      }
    }
    c = inv(S[k][k], p);
    S[k][k] = 1;
    for (j = k+1; j < n; j++) {
      S[k][j] = (S[k][j] * c) % p;
    }
    for (i = k+1; i < n; i++) {
      c = p - S[i][k];
      S[i][k] = 0;
      for (j = k+1; j < n; j++) {
	S[i][j] = (S[i][j] + c * S[k][j]) % p;
      }
    }
  }
  return rank;
}

int main(void)
{
  int p;
  int n1, n2;
  int poly1[101], poly2[101];
  int S[200][200];  /* sylvester matrix */
  int i, rank, deg;
  int case_num = 1;

  while (scanf("%d", &p) == 1 && p) {
    n1 = read_poly(poly1, p);
    n2 = read_poly(poly2, p);
    form_syl(S, n1, poly1, n2, poly2);
    rank = reduce(S, n1+n2, p);
    deg = n1+n2 - rank;
    printf("Case %d: %d", case_num++, deg);
    for (i = deg; i >= 0; i--) {
      printf(" %d", S[rank-1][n1+n2-1-i]);
    }
    printf("\n");
  }
  return 0;
}
