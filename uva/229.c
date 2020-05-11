#include <stdio.h>
#include <assert.h>

#define ROWS 10
#define COLS 15
#define SENSORS 24

/* number of sensors in each array */
int array_size[4] = {10,24,15,24};

/* every cell is in one sensor for each array...store which sensor
   it is */
int lines[ROWS][COLS][4];

typedef int Sensors[4][SENSORS];

int start[4][SENSORS][2];
int dir[4][2] = { {0, 1}, {-1, 1}, {1, 0}, {-1,-1} };

/* length of each scanline */
Sensors length;

void fill_line(int sr, int sc, int l, int index)
{
  start[l][index][0] = sr;
  start[l][index][1] = sc;
  while (0 <= sr && sr < ROWS && 0 <= sc && sc < COLS) {
    lines[sr][sc][l] = index;
    sr += dir[l][0];
    sc += dir[l][1];
    length[l][index]++;
  }
}

void fill_lines(void)
{
  int i, k;

  /* array 1 */
  for (i = 0; i < ROWS; i++) {
    fill_line(i, 0, 0, i);
  }
  
  /* array 2 */
  for (i = k = 0; i < ROWS; i++) {
    fill_line(i, 0, 1, k++);
  }
  for (i = 1; i < COLS; i++) {
    fill_line(ROWS-1, i, 1, k++);
  }

  /* array 3 */
  for (i = 0; i < COLS; i++) {
    fill_line(0, i, 2, i);
  }
  
  /* array 4 */
  for (i = k = 0; i < COLS; i++) {
    fill_line(ROWS-1, i, 3, k++);
  }
  for (i = ROWS-2; i >= 0; i--) {
    fill_line(i, COLS-1, 3, k++);
  }
}

char solution[ROWS][COLS+1];
int num_sol;

void find_cell(char board[ROWS][COLS+1], int array, int sensor, int *r, int *c)
{
  *r = start[array][sensor][0];
  *c = start[array][sensor][1];

  while (0 <= *r && *r < ROWS && 0 <= *c && *c < COLS) {
    if (!board[*r][*c] && lines[*r][*c][array] == sensor) {
      return;
    }
    *r += dir[array][0];
    *c += dir[array][1];
  }
  printf("array = %d, sensor = %d\n", array, sensor);
  assert(0);
}

void update(int r, int c, Sensors num, int inc)
{
  int k;

  for (k = 0; k < 4; k++) {
    num[k][lines[r][c][k]] += inc;
  }
}

int check(int r, int c, Sensors input, Sensors num_black, Sensors num_white)
{
  int k;

  for (k = 0; k < 4; k++) {
    if (num_black[k][lines[r][c][k]] > input[k][lines[r][c][k]]) {
      return 0;
    }
    if (num_black[k][lines[r][c][k]] + num_white[k][lines[r][c][k]] >
	length[k][lines[r][c][k]]) {
      return 0;
    }
  }
  return 1;
}

void solve(char board[ROWS][COLS+1], Sensors input, Sensors num_white,
	  Sensors num_black, int num_filled)
{
  int i, j, r, c, left;
  
  if (num_filled >= ROWS*COLS) {
    /* check that we actually have a solution */
    for (i = 0; i < 4; i++) {
      for (j = 0; j < array_size[i]; j++) {
	if (input[i][j] != num_black[i][j]) {
	  return;
	}
      }
    }
    
    /* we are done! */
    if (!(num_sol++)) {
      for (i = 0; i < ROWS; i++) {
	for (j = 0; j <= COLS; j++) {
	  solution[i][j] = board[i][j];
	}
      }
    }
    return;
  }

  /* look for a line which is forced */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < array_size[i]; j++) {
      left = length[i][j] - num_white[i][j] - num_black[i][j];

      /* line is already filled */
      if (!left) continue;

      /* the rest of the line must be all white */
      if (num_black[i][j] == input[i][j]) {
	find_cell(board, i, j, &r, &c);
	board[r][c] = '.';  update(r, c, num_white, 1);
	if (check(r, c, input, num_black, num_white)) {
	  solve(board, input, num_white, num_black, num_filled+1);
	}
	board[r][c] = 0;    update(r, c, num_white, -1);
	return;
      }

      /* the rest of the line must be all black */
      if (input[i][j] - num_black[i][j] == left) {
	find_cell(board, i, j, &r, &c);
	board[r][c] = '#';  update(r, c, num_black, 1);
	if (check(r, c, input, num_black, num_white)) {
	  solve(board, input, num_white, num_black, num_filled+1);
	}
	board[r][c] = 0;    update(r, c, num_black, -1);
	return;
      }
    }
  }

  /* no line that is forced, just look for any cell and try both */
  for (r = 0; r < ROWS; r++) {
    for (c = 0; c < COLS; c++) {
      if (!board[r][c]) {
	/* try white */
	board[r][c] = '.';  update(r, c, num_white, 1);
	if (check(r, c, input, num_black, num_white)) {
	  solve(board, input, num_white, num_black, num_filled+1);
	}
	board[r][c] = 0;    update(r, c, num_white, -1);

	/* try black */
	board[r][c] = '#';  update(r, c, num_black, 1);
	if (check(r, c, input, num_black, num_white)) {
	  solve(board, input, num_white, num_black, num_filled+1);
	}
	board[r][c] = 0;    update(r, c, num_black, -1);

	return;
      }
    }
  }

}

int main(void)
{
  int slices;
  Sensors input, num_white, num_black;
  char board[ROWS][COLS+1];
  int i, j;

  fill_lines();

  scanf("%d", &slices);

  while (slices-- > 0) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < array_size[i]; j++) {
	scanf("%d", input[i]+j);
	num_white[i][j] = num_black[i][j] = 0;
      }
    }
    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLS; j++) {
	board[i][j] = 0;
      }
      board[i][COLS] = 0;
    }
    
    num_sol = 0;
    solve(board, input, num_white, num_black, 0);
    if (num_sol == 1) {
      for (i = 0; i < ROWS; i++) {
	printf("%s\n", solution[i]);
      }
    } else {
      for (i = 0; i < ROWS; i++) {
	for (j = 0; j < COLS; j++) {
	  printf(".");
	}
	printf("\n");
      }
    }

    if (slices) {
      printf("\n");
    }
  }

  
  return 0;
}
