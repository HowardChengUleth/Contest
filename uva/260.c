/*
 * Union-find algorithm for equivalence classes
 *
 * Author: Howard Cheng
 *
 * Given n labels (0, 1, ..., n-1), the union and find operations are
 * implemented for equivalence classes computation.
 *
 * Revised: 21 June 2000 by Howard Cheng <hchcheng@scg.math.uwaterloo.ca>
 *   - use weighted union (cf. Cormen, Leiserson, Rivest, Ch. 22) to improve
 *     amortized run time
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int p, rank;
} UnionFind;

void init_uf(UnionFind *uf, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    uf[i].p = i;
    uf[i].rank = 0;
  }
}

int find(UnionFind *uf, int x)
{
  if (uf[x].p != x) {
    uf[x].p = find(uf, uf[x].p);
  }
  return uf[x].p;
}

void merge(UnionFind *uf, int x, int y)
{
  int res1, res2;

  res1 = find(uf, x);
  res2 = find(uf, y);
  if (res1 != res2) {
    if (uf[res1].rank > uf[res2].rank) {
      uf[res2].p = res1;
    } else {
      uf[res1].p = res2;
      if (uf[res1].rank == uf[res2].rank) {
	uf[res2].rank++;
      }
    }
  }
}

#include <stdio.h>

char board[200][201];

int read_case(void)
{
  int N, i;

  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%s", board[i]);
  }
  return N;
}

int to_index(int i, int j, int N)
{
  return i*N+j;
}

void solve_case(int N)
{
  UnionFind uf[200*200+2];
  const int LEFT = 200*200, 
    RIGHT = 200*200+1;
  int di[6] = {-1, -1, 0, 0, 1, 1};
  int dj[6] = {-1, 0, -1, 1, 0, 1};
  int i, j, k, ni, nj;

  /* only have to see if white wins, otherwise black must win */
  init_uf(uf, 200*200+2);
  for (i = 0; i < N; i++) {
    if (board[i][0] == 'w') {
      merge(uf, to_index(i, 0, N), LEFT);
    }
    if (board[i][N-1] == 'w') {
      merge(uf, to_index(i, N-1, N), RIGHT);
    }
  }
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (board[i][j] != 'w') continue;
      for (k = 0; k < 6; k++) {
	ni = i + di[k];
	nj = j + dj[k];
	if (!(0 <= ni && ni < N && 0 <= nj && nj < N) ||
	    board[ni][nj] != 'w') continue;
	merge(uf, to_index(i, j, N), to_index(ni, nj, N));
      }
    }
  }

  if (find(uf, LEFT) == find(uf, RIGHT)) {
    printf("W\n");
  } else {
    printf("B\n");
  }
}

int main(void)
{
  int N;
  int case_num = 1;

  while (N = read_case()) {
    printf("%d ", case_num++);
    solve_case(N);
  }

  return 0;
}
