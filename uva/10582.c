/* @JUDGE_ID: 1102NT 10582 C "" */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_DIM 64

/* represent pieces as follows:

   0 = empty
   1 = vertical line
   2 = horizontal line
   3 = NE corner
   4 = SE corner
   5 = SW corner
   6 = NW corner

*/

char pieces[7][3][4] = {
  {{"   "},
   {"   "},
   {"   "}},

  {{" * "},
   {" * "},
   {" * "}},

  {{"   "},
   {"***"},
   {"   "}},

  {{" * "},
   {" **"},
   {"   "}},

  {{"   "},
   {" **"},
   {" * "}},

  {{"   "},
   {"** "},
   {" * "}},

  {{" * "},
   {"** "},
   {"   "}}
};

typedef enum {N = 0, E, S, W} Direction;

char exits[7][4] = {
  {0,0,0,0},
  {1,0,1,0},
  {0,1,0,1},
  {1,1,0,0},
  {0,1,1,0},
  {0,0,1,1},
  {1,0,0,1}
};

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
Direction opp[4] = {S, W, N, E};

typedef struct {
  int r, c, piece;
} Move;

int board[MAX_DIM][MAX_DIM];
char used[MAX_DIM][MAX_DIM];
int m, n;

int sol_count, path_len;
Move path[MAX_DIM];

int symbol(char buffer[MAX_DIM*4+1][MAX_DIM*4+3], int r, int c)
{
  int i, k;

  for (k = 0; k < 7; k++) {
    for (i = 0; i < 3; i++) {
      if (strncmp(&(buffer[r+i][c]), pieces[k][i], 3)) {
	break;
      }
    }
    if (i == 3) {
      switch (k) {
      case 0:
	return 0;
      case 1: case 2:
	return 1;
      case 3: case 4: case 5: case 6:
	return 3;
      }
    }
  }
  assert(0);
  return -1;
}


void read_board(void)
{
  char buffer[MAX_DIM*4+1][MAX_DIM*4+3];
  int i, j;

  scanf("%d %d\n", &m, &n);
  for (i = 0; i < m*4+1; i++) {
    fgets(buffer[i], MAX_DIM*4+3, stdin);
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      board[i][j] = symbol(buffer, 4*i+1, 4*j+1);
    }
  }
}

void search(int r, int c, Direction d, Move *curr_path, int index)
{
  int p = board[r][c], q;
  int i;
  Direction d2;

  /*
  for (i = 0; i < index*2; i++) {
    putchar(' ');
  }
  printf("r = %d, c = %d, Direction = %d\n", r, c, d);
  */

  if ((r == m && c == n-1) || (r == m-1 && c == n)) {
    /* we found a path */

    if (!sol_count || index < path_len) {
      for (i = 0; i < index; i++) {
	path[i] = curr_path[i];
      }
      path_len = index;
    }
    
    sol_count++;
    return;
  }

  if (r < 0 || c < 0 || r >= m || c >= n || used[r][c] || p == 0) {
    /* no way to continue, quit */
    return;
  }

  q = (p == 1) ? 2 : 4;

  used[r][c] = 1;
  curr_path[index].r = r;
  curr_path[index].c = c;
  for (i = p; i < p+q; i++) {
    if (!exits[i][d]) continue;
    curr_path[index].piece = i;

    for (d2 = 0; d2 < 4; d2++) {
      if (exits[i][d2] && d2 != d) {
	break;
      }
    }

    search(r + dr[d2], c + dc[d2], opp[d2], curr_path, index+1);
  }
  used[r][c] = 0;
}

void print_path(void)
{
  char buffer[MAX_DIM*4+1][MAX_DIM*4+3];
  int i, j, k;

  for (i = 0; i < 4*m+1; i++) {
    for (j = 0; j < 4*n+1; j++) {
      buffer[i][j] = ' ';
    }
    buffer[i][4*n+1] = 0;
  }

  for (i = 0; i <= m; i++) {
    for (j = 0; j < 4*n+1; j++) {
      buffer[4*i][j] = (j % 4 == 0) ? '+' : '-';
    }
  }
  for (j = 0; j <= n; j++) {
    for (i = 0; i < 4*m+1; i++) {
      buffer[i][4*j] = (i % 4 == 0) ? '+' : '|';
    }
  }

  for (k = 0; k < path_len; k++) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
	buffer[path[k].r*4+1+i][path[k].c*4+1+j] = 
	  pieces[path[k].piece][i][j];
      }
    }
  }

  for (i = 0; i < 4*m+1; i++) {
    printf("%s\n", buffer[i]);
  }
}

void solve_board(void)
{
  Move curr_path[MAX_DIM];
  int i, j;

  sol_count = 0;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      used[i][j] = 0;
    }
  }

  search(0, 0, N, curr_path, 0);
  search(0, 0, W, curr_path, 0);

  if (sol_count) {
/*    print_path(); */
  }
  printf("Number of solutions: %d\n", sol_count);
}

int main(void)
{
  int c;

  scanf("%d", &c);
  while (c-- > 0) {
    read_board();
    solve_board();
  }

  return 0;
}
