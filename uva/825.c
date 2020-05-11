/* @JUDGE_ID: 1102NT 825 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void solve_case(void)
{
  int W, N;
  int **paths;
  int i, j;
  int row, col;
  char buffer[1024], *p;

  scanf("%d %d\n", &W, &N);
  paths = malloc(W*sizeof(*paths));
  assert(paths);
  for (i = 0; i < W; i++) {
    paths[i] = malloc(N*sizeof(int));
    assert(paths[i]);
    for (j = 0; j < N; j++) {
      paths[i][j] = 0;
    }
  }

  for (i = 0; i < W; i++) {
    fgets(buffer, 1024, stdin);
    p = strtok(buffer, " \n");
    row = atoi(p) - 1;
    while (p = strtok(0, " \n")) {
      col = atoi(p) - 1;
      paths[row][col] = -1;
    }
  }

  paths[0][0] = (paths[0][0] >= 0) ? 1 : 0;

  for (j = 1; j < N; j++) {
    paths[0][j] = (paths[0][j] < 0) ? 0 : paths[0][j-1];
  }
  for (i = 1; i < W; i++) {
    paths[i][0] = (paths[i][0] < 0) ? 0 : paths[i-1][0];
    for (j = 1; j < N; j++) {
      paths[i][j] = (paths[i][j] < 0) ? 0 : paths[i-1][j] + paths[i][j-1];
    }
  }

  printf("%d\n", paths[W-1][N-1]);

  for (i = 0; i < W; i++) {
    free(paths[i]);
  }
  free(paths);
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
    if (cases) {
      printf("\n");
    }
  }
  return 0;
}
