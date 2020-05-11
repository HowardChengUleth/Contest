/* @JUDGE_ID: 1102NT 114 C "" */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM 51

typedef struct {
  char is_bumper;
  int value;
  int cost;
} Cell;

int m, n;
int wallcost;
Cell grid[MAX_DIM][MAX_DIM];

int simulate(int x, int y, int dir, int life);

int main(void) {
  int p, i;
  int x, y;
  int dir, life;
  int total = 0;

  scanf("%d %d", &m, &n);
  scanf("%d", &wallcost);
  scanf("%d", &p);

  for (x = 1; x <= m; x++) {
    for (y = 1; y <= n; y++) {
      grid[x][y].is_bumper = 0;
    }
  }
  for (i = 0; i < p; i++) {
    scanf("%d %d", &x, &y);
    grid[x][y].is_bumper = 1;
    scanf("%d %d", &(grid[x][y].value), &(grid[x][y].cost));
  }

  while (scanf("%d %d %d %d", &x, &y, &dir, &life) == 4) {
    int score = simulate(x, y, dir, life);
    total += score;
    printf("%d\n", score);
  }
  printf("%d\n", total);

  return 0;
}

int simulate(int x, int y, int dir, int life)
{
  int score = 0;
  int newx, newy;

  while (--life > 0) {
    newx = x;
    newy = y;
    switch (dir) {
    case 0: 
      newx++;
      break;
    case 1:
      newy++;
      break;
    case 2:
      newx--;
      break;
    case 3:
      newy--;
      break;
    default:
      fprintf(stderr, "Invalid case...\n");
      exit(1);
    }

    /* check to see if the new coords is a bumper or wall */
    if (newx == 1 || newx == m || newy == 1 || newy == n) {
      /* on wall */
      life -= wallcost;
      dir = (dir + 3) % 4;
    } else if (grid[newx][newy].is_bumper) {
      /* on bumper */
      score += grid[newx][newy].value;
      life -= grid[newx][newy].cost;
      dir = (dir + 3) % 4;
    } else {
      /* not on anything, just move */
      x = newx;
      y = newy;
    }
  }
  return score;
}
