/* @JUDGE_ID: 1102NT 10558 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char map[100][100];
int N, S, A;
int streets[100];

int friendly[101][101];
int F[101][101];
int best_j[101][101];

void compute_friendly(void)
{
  int count[101][101];
  int i, j, s, t;
  int area, good;

  for (i = 1; i < 100; i++) {
    for (s = 0; s < S-1; s++) {
      count[i][s] = 0;
      for (j = streets[s]; j < streets[s+1]; j++) {
	if (map[i][j]) {
	  count[i][s]++;
	}
      }
    }
  }

  for (i = 1; i <= 100; i++) {
    friendly[i][i] = 0;
    for (j = i+1; j <= 100; j++) {
      friendly[i][j] = 0;
      for (s = 0; s < S-1; s++) {
	good = 0;
	for (t = i; t < j; t++) {
	  good += count[t][s];
	}
	area = (j-i)*(streets[s+1]-streets[s]);
	if (good > 0) {
	  friendly[i][j]++;
	}
      }
    }
  }
}

void compute_F(void)
{
  int n, a, j;

  for (n = 2; n <= 100; n++) {
    F[n][2] = friendly[1][n];
    best_j[n][2] = -1;
  }
  for (a = 3; a <= A; a++) {
    for (n  = 0; n <= 100; n++) {
      if (a > n) {
	F[n][a] = -1;
	best_j[n][a] = -1;
      } else {
	F[n][a] = -1;
	best_j[n][a] = -1;
	for (j = 2; j < n; j++) {
	  if (F[j][a-1] != -1 && F[j][a-1] + friendly[j][n] > F[n][a]) {
	    F[n][a] = F[j][a-1] + friendly[j][n];
	    best_j[n][a] = j;
	  }
	}
      }
    }
  }
}

void print_soln(void)
{
  int soln[100], n = 0;
  int i = 100, k = A;

  while (k > 1) {
    soln[n++] = i;
    i = best_j[i][k--];
    /*
      assert(i > 0);
    */
  }
  soln[n++] = 1;

  printf("%d", A);
  for (i = n-1; i >= 0; i--) {
    printf(" %d", soln[i]);
  }
  printf("\n");
}



int main(void)
{
  int i, j, k;

  while (scanf("%d", &N) == 1 && N != -1) {
    memset(map, 0, sizeof(map));
    for (k = 0; k < N; k++) {
      scanf("%d %d", &i, &j);
      map[j][i] = 1;
    }
    scanf("%d", &S);
    for (k = 0; k < S; k++) {
      scanf("%d", streets+k);
    }
    scanf("%d", &A);

    compute_friendly();
    compute_F();
    print_soln();
  }
  return 0;
}
