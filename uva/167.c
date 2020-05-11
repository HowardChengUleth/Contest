#include <stdio.h>

int board[8][8];

int search(int *perm, int start, int n, int part_sum)
{
  int i, t;
  int j, good;
  int best = -1;

  if (start == n) {
    return part_sum;
  }

  for (i = start; i < n; i++) {
    t = perm[start];
    perm[start] = perm[i];
    perm[i] = t;

    good = 1;
    for (j = 0; j < start; j++) {
      if (perm[j] - perm[start] == start - j ||
	  perm[start] - perm[j] == start - j) {
	good = 0;
      }
    }
    if (good) {
      if ((t = search(perm, start+1, n, part_sum + board[j][perm[j]])) > best) {
	best = t;
      }
    }

    t = perm[start];
    perm[start] = perm[i];
    perm[i] = t;
  }
  return best;
}

void solve(void)
{
  int perm[8];
  int i, j;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      scanf("%d", &board[i][j]);
    }
    perm[i] = i;
  }

  printf("%5d\n", search(perm, 0, 8, 0));
}

int main(void)
{
  int k;

  scanf("%d", &k);
  while (k-- > 0) {
    solve();
  }
  return 0;
}
