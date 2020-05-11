/* @JUDGE_ID: 1102NT 756 C "" */
/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int m[3], a[3], g[3];

int inverse(int a, int b)
{
  int r, r1, a1, b1, q;
  int A = a;
  int B = b;

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

  assert(a == 1);
  return a1;
}

int cra(int n, int *m, int *a)
{
  int x, i, k, temp;
  int v[3];

  v[0] = a[0];
  for (k = 1; k < n; k++) {
    temp = v[k-1];
    for (i = k-2; i >= 0; i--) {
      temp = (temp * m[i] + v[i]) % m[k];
      if (temp < 0) {
	temp += m[k];
      }
    }
    v[k] = ((a[k] - temp) * g[k]) % m[k];
    if (v[k] < 0) {
      v[k] += m[k];
    }
  }

  x = v[n-1];
  for (k = n-2; k >= 0; k--) {
    x = x * m[k] + v[k];
  } 

  return x;
}


void solve_case(void)
{
  int d, M, x, i, k, prod, case_num;
  int t;

  m[0] = 23;
  m[1] = 28;
  m[2] = 33;
  M = 23*28*33;

  for (k = 1; k < 3; k++) {
    prod = m[0] % m[k];
    for (i = 1; i < k; i++) {
      prod = (prod * m[i]) % m[k];
    }
    g[k] = inverse(prod, m[k]) % m[k];
    if (g[k] < 0) {
      g[k] += m[k];
    }
  }


  for (case_num = 1; 
       (t = scanf("%d %d %d %d", a, a+1, a+2, &d)) == 4 && 
	 a[0] != -1 && a[1] != -1 && a[2] != -1 && d != -1;
       case_num++) {
    assert(0 <= d && d <= 365);
    for (i = 0; i < 3; i++) {
      assert(0 <= a[i] && a[i] <= 365);
      a[i] %= m[i];
    }
    x = cra(3, m, a);
    if (x <= d) {
      x += ((d-x) / M + 1) * M;
    }
    printf("Case %d: the next triple peak occurs in %d days.\n", case_num,
	   x-d);
  }
  assert(t == 4);
  assert(a[0] == a[1] && a[1] == a[2] && a[2] == d && d == -1);
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
