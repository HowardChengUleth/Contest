#include <stdio.h>

int main(void)
{
  int T, N, R;
  int u, v;
  int i, j, k;
  int G[100][100];
  int c;
  int ans;


  scanf("%d", &T);
  for (c = 1; c <= T; c++) {
    printf("Case %d: ", c);
    scanf("%d", &N);
    for (u = 0; u < N; u++) {
      for (v = 0; v < N; v++) {
	G[u][v] = -1;
      }
      G[u][u] = 0;
    }
    scanf("%d", &R);
    while (R-- > 0) {
      scanf("%d %d", &u, &v);
      G[u][v] = G[v][u] = 1;
    }
    for (k = 0; k < N; k++) {
      for (i = 0; i < N; i++) {
	if (G[i][k] == -1) continue;
	for (j = 0; j < N; j++) {
	  if (G[k][j] == -1) continue;
	  if (G[i][j] == -1 || G[i][k] + G[k][j] < G[i][j]) {
	    G[i][j] = G[i][k] + G[k][j];
	  }
	}
      }
    }
    
    scanf("%d %d", &u, &v);
    ans = G[u][0] + G[0][v];
    for (i = 1; i < N; i++) {
      if (G[u][i] + G[i][v] > ans) {
	ans = G[u][i] + G[i][v];
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
  
