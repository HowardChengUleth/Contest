/* @JUDGE_ID: 1102NT 10616 C "" */

#include <stdio.h>

int main(void)
{
  int set = 0;
  int N, Q, D, M;
  long long num[200];
  long long ways[201][11][20];
  int i;
  int n, d, m;
  int t;

  while (scanf("%d %d", &N, &Q) == 2 && (N || Q)) {
    printf("SET %d:\n", ++set);
    for (i = 0; i < N; i++) {
      scanf("%lld", num+i);
    }

    for (i = 1; i <= Q; i++) {
      scanf("%d %d", &D, &M);
      printf("QUERY %d: ", i);
      
      ways[0][0][0] = 1;
      for (d = 1; d < D; d++) {
	ways[0][0][d] = 0;
      }
      for (n = 1; n <= N; n++) {
	/* n choose 0 */
	ways[n][0][0] = 1;
	for (d = 1; d < D; d++) {
	  ways[n][0][d] = 0;
	}

	/* the rest */
	for (m = 1; m <= M; m++) {
	  if (m > n) {
	    for (d = 0; d < D; d++) {
	      ways[n][m][d] = 0;
	    }
	    continue;
	  }
	  for (d = 0; d < D; d++) {
	    ways[n][m][d] = (n-1 >= m) ? ways[n-1][m][d] : 0;
	  }
	  for (d = 0; d < D; d++) {
	    t = num[n-1] % D;
	    if (t < 0) {
	      t += D;
	    }
	    ways[n][m][(d+t)%D] += ways[n-1][m-1][d];
	  }
	}
      }

      printf("%lld\n", ways[N][M][0]);
    }
  }
  return 0;
}
