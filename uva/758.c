/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ROWS 10
#define COLS 15
#define BONUS 1000
#define BLANK '.'

char board[ROWS][COLS];
char *colors = "RGB";

static int region(char mark[ROWS][COLS], int r, int c)
{
  int sum;

  if (board[r][c] == BLANK || mark[r][c]) {
    return 0;
  }
  
  mark[r][c] = 1;
  sum = 1;

  if (r > 0 && board[r-1][c] == board[r][c]) {
    sum += region(mark, r-1, c);
  }
  if (r < ROWS-1 && board[r+1][c] == board[r][c]) {
    sum += region(mark, r+1, c);
  }
  if (c > 0 && board[r][c-1] == board[r][c]) {
    sum += region(mark, r, c-1);
  }
  if (c < COLS-1 && board[r][c+1] == board[r][c]) {
    sum += region(mark, r, c+1);
  }
  
  return sum;
}

static int next_move(int *r, int *c)
{
  char mark[ROWS][COLS];
  int i, j, t, best_r, best_c, best_val = 0;

  /* clear marks */
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      mark[i][j] = 0;
    }
  }

  /* find the best spot */
  for (j = 0; j < COLS; j++) {
    for (i = 0; i < ROWS; i++) {
      if ((t = region(mark, i, j)) > best_val) {
	best_val = t;
	best_r = i;
	best_c = j;
      }
    }
  }

  *r = best_r;
  *c = best_c;
  return best_val;
}

static void remove_ball(int r, int c)
{
  char t = board[r][c];

  board[r][c] = BLANK;
  if (r > 0 && board[r-1][c] == t) {
    remove_ball(r-1, c);
  }
  if (r < ROWS-1 && board[r+1][c] == t) {
    remove_ball(r+1, c);
  }
  if (c > 0 && board[r][c-1] == t) {
    remove_ball(r, c-1);
  }
  if (c < COLS-1 && board[r][c+1] == t) {
    remove_ball(r, c+1);
  }
}

static void compress_board(void)
{
  int i, j, k1, k2;

  /* compress each column first */
  for (j = 0; j < COLS; j++) {
    k1 = k2 = 0;
    while (k2 < ROWS) {
      if (board[k2][j] != BLANK) {
	board[k1++][j] = board[k2][j];
      }
      k2++;
      assert(k1 <= k2);
    }
    while (k1 < ROWS) {
      board[k1++][j] = BLANK;
    }
  }

  /* shift the columns to the left */
  k1 = k2 = 0;
  while (k2 < COLS) {
    if (board[0][k2] != BLANK) {
      /* copy columns */
      if (k1 != k2) {
	for (i = 0; i < ROWS; i++) {
	  board[i][k1] = board[i][k2];
	}
      }
      k1++;
    }
    k2++;
    assert(k1 <= k2);
  }
  while (k1 < COLS) {
    for (i = 0; i < ROWS; i++) {
      board[i][k1] = BLANK;
    }
    k1++;
  }
}

static void write_board(void)
{
  int i, j;

  printf("--------------------------------------------\n");
  for (i = ROWS-1; i >= 0; i--) {
    for (j = 0; j < COLS; j++) {
      putchar(board[i][j]);
    }
    putchar('\n');
  }
  printf("--------------------------------------------\n");
}

static void read_board(void)
{
  int i, j, c;

  c = getchar();
  assert(c == '\n');
  for (i = ROWS-1; i >= 0; i--) {
    for (j = 0; j < COLS; j++) {
      board[i][j] = getchar();
      assert(strchr(colors, board[i][j]));
    }
    c = getchar();
    assert(c == '\n');
  }
}

static void solve_game(void)
{
  int r, c, score = 0, remain = ROWS*COLS, t, m, moves = 0;
  
  while (remain > 1 && (m = next_move(&r, &c)) > 1) {
    t = (m-2) * (m-2);
    score += t;
    remain -= m;
    printf("Move %d at (%d,%d): "
	   "removed %d balls of color %c, got %d points.\n",
	   ++moves, r+1, c+1, m, board[r][c], t);
    remove_ball(r,c);
    compress_board();
/*    write_board(); */
  }

  if (!remain) {
    score += BONUS;
  }
  printf("Final score: %d, with %d balls remaining.\n", score, remain);
}

void solve_case(void)
{
  int n, c, i, t;

  t = scanf("%d", &n);
  assert(t == 1 && n > 0);
  c = getchar();
  assert(c == '\n');

  for (i = 0; i < n; i++) {
    if (i > 0) {
      printf("\n");
    }
    printf("Game %d:\n\n", i+1);
    read_board();
    solve_game();
  }
}

int main(void)
{
  solve_case();
  return 0;
}
