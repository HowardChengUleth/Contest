/* @JUDGE_ID: 1102NT 662 C "" */

#include <stdio.h>

#define MAX_N 200
#define MAX_K 30

int n, k;
int d[MAX_N];

int read_case(void)
{
  int i;

  scanf("%d %d", &n, &k);
  if (!n && !k) {
    return 0;
  }
  for (i = 0; i < n; i++) {
    scanf("%d", d+i);
  }

  return 1;
}

void solve_case(void)
{
  int best[MAX_N+1][MAX_K+1];
  int cut[MAX_N][MAX_K+1];
  int i, j, l, med, depot;

  int D[MAX_N][MAX_N];  /* D[i,j] = minimum distance sum for restaurants i..j
			   if one depot is placed there */

  for (i = 0; i < n; i++) {
    D[i][i] = 0;
    for (j = i+1; j < n; j++) {
      med = (j-i)/2 + i;
      D[i][j] = D[i][j-1] + d[j] - d[med];
    }
  }

  /* base cases */
  for (j = 1; j <= k; j++) {
    best[n-1][j] = D[n-1][n-1];
    cut[n-1][j] = n;
    best[n][j] = 0;
  }


  /* induction step */
  for (i = n-2; i >= 0; i--) {
    for (j = 1; j <= k; j++) {
      med = (cut[i+1][j]-i)/2 + i;

      /* first, assume we don't add more depots */
      best[i][j] = best[i+1][j] + d[med] - d[i];
      cut[i][j] = cut[i+1][j];

      /* now try adding one more depot */
      if (j == 1) continue;

      for (l = i; l < n; l++) {
	if (D[i][l] + best[l+1][j-1] < best[i][j]) {
	  best[i][j] = D[i][l] + best[l+1][j-1];
	  cut[i][j] = l+1;
	}
      }
    }
  }

  i = 0;
  j = k;
  depot = 1;
  do {
    med = (cut[i][j]-i)/2 + i;
    printf("Depot %d at restaurant %d serves ", depot++, med+1);
    if (cut[i][j]-i == 1) {
      printf("restaurant %d\n", i+1);
    } else {
      printf("restaurants %d to %d\n", i+1, cut[i][j]);
    }
    i = cut[i][j--];
  } while (i < n);


  printf("Total distance sum = %d\n", best[0][k]);
}

int main(void)
{
  int cases = 0;
  while (read_case()) {
    printf("Chain %d\n", ++cases);
    solve_case();
    printf("\n");
  }
  return 0;
}
