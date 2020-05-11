/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <assert.h>

#define MAX_LAKE 25
#define MAX_HOUR 16
#define MAX_MIN5 MAX_HOUR*12

int n, min5, F[MAX_LAKE], d[MAX_LAKE], t[MAX_LAKE];

int read_case(void)
{
  int i, r;
  
  r = scanf("%d", &n);
  if (!n) {
    return 0;
  }
  assert(r == 1);

  assert(1 <= n && n <= MAX_LAKE);
  r = scanf("%d", &min5);
  min5 *= 12;
  assert(r == 1 && 12 <= min5 && min5 <= MAX_MIN5);

  for (i = 0; i < n; i++) {
    r = scanf("%d", F+i);
    assert(r == 1 && F[i] >= 0);
  }
  for (i = 0; i < n; i++) {
    r = scanf("%d", d+i);
    assert(r == 1 && d[i] >= 0);
  }
  for (i = 0; i < n-1; i++) {
    r = scanf("%d", t+i);
    assert(r == 1 && 0 < t[i] && t[i] <= MAX_MIN5);
  }

  return 1;
}

void solve_case(void)
{
  /* max number of fish we can get starting at lake i, with 5*j minutes used */
  int fishes[MAX_LAKE][MAX_MIN5];

  /* how long we fish at lake i */
  int len[MAX_LAKE][MAX_MIN5];
  int i, j, k, sum, dec, f, temp;

  /* fill base case */
  sum = dec = 0;
  for (j = min5-1; j >= 0; j--) {
    if ((f = F[n-1] - dec) < 0) {
      f = 0;
    }
    sum += f;
    fishes[n-1][j] = sum;
    len[n-1][j] = min5-j;
    dec += d[n-1];
  }

  /* compute table */
  for (i = n-2; i >= 0; i--) {
    for (j = min5-1; j >= 0; j--) {
      sum = dec = 0;
      fishes[i][j] = -1;
      for (k = 0; k <= min5-j; k++) {
	if (j+k+t[i] < min5) {
	  /* fish 5*k minutes, then move on */
	  temp = fishes[i+1][j+k+t[i]] + sum; 
	} else {
	  /* just stay here for the rest of time */
	  temp = sum;
	}

	if (temp >= fishes[i][j]) {
	  fishes[i][j] = temp;
	  len[i][j] = k;
	}
	if ((f = F[i] - dec) < 0) {
	  f = 0;
	}
	sum += f;
	dec += d[i];
      }
    }
  }

  /* now print the solution */
  for (i = j = 0; i < n; i++) {
    if (i) {
      printf(", ");
    }
    if (j < min5) {
      printf("%d", len[i][j]*5);
      if (i < n) {
	j += len[i][j] + t[i];
      }
    } else {
      printf("0");
    }
  }
  printf("\n");
  printf("Number of fish expected: %d\n", fishes[0][0]);
}


void solve_file(void)
{
  int first = 1;

  while (read_case()) {
    if (!first) {
      printf("\n");
    }
    solve_case();
    first = 0;
  }
}

int main(void)
{
  solve_file();
  return 0;
}
