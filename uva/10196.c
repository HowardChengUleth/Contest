#include <stdio.h>
#include <ctype.h>

char board[10][9];
char attack[10][10];

int read_board(void)
{
  int i, j;

  for (i = 1; i <= 8; i++) {
    scanf("%s", board[i]+1);
  }
  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      if (board[i][j] != '.') {
	return 1;
      }
    }
  }
  return 0;
}

void pawn(int r, int c)
{
  int dr = (islower(board[r][c])) ? 1 : -1;
  attack[r+dr][c-1] = attack[r+dr][c+1] = 1;
}

void lines(int r, int c, int *dr, int *dc, int ndir)
{
  int r2, c2;
  int d;

  for (d = 0; d < ndir; d++) {
    r2 = r + dr[d];
    c2 = c + dc[d];
    while (1 <= r2 && r2 <= 8 && 1 <= c2 && c2 <= 8) {
      attack[r2][c2] = 1;
      if (board[r2][c2] != '.') {
	break;
      }
      r2 += dr[d];
      c2 += dc[d];
    }
  }
}

void rook(int r, int c)
{
  int dr[4] = {-1, 1, 0, 0};
  int dc[4] = {0, 0, -1, 1};
  lines(r, c, dr, dc, 4);
}

void bishop(int r, int c)
{
  int dr[4] = {-1, -1, 1, 1};
  int dc[4] = {-1, 1, -1, 1};
  lines(r, c, dr, dc, 4);
}

void queen(int r, int c)
{
  int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  lines(r, c, dr, dc, 8);
}

void king(int r, int c)
{
  int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int i;

  for (i = 0; i < 8; i++) {
    attack[r+dr[i]][c+dc[i]] = 1;
  }
}

void knight(int r, int c)
{
  int i, j;
  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      if (((r-i == 2 || i-r == 2) && (j-c == 1 || c-j == 1)) ||
	  ((j-c == 2 || c-j == 2) && (r-i == 1 || i-r == 1))) {
	attack[i][j] = 1;
      }
    }
  }
}

int isblack(char c)
{
  return islower(c);
}

int iswhite(char c)
{
  return isupper(c);
}

int check(int (*myside)(char c))
{
  int i, j;

  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      attack[i][j] = 0;
    }
  }

  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      if (!myside(board[i][j])) continue;
      switch(tolower(board[i][j])) {
      case 'p':
	pawn(i, j);
	break;
      case 'r':
	rook(i, j);
	break;
      case 'b':
	bishop(i, j);
	break;
      case 'q':
	queen(i, j);
	break;
      case 'k':
	king(i, j);
	break;
      case 'n':
	knight(i, j);
	break;
      }
    }
  }
  
  for (i = 1; i <= 8; i++) {
    for (j = 1; j <= 8; j++) {
      if (attack[i][j] && tolower(board[i][j]) == 'k' && !myside(board[i][j])) {
	return 1;
      }
    }
  }
  return 0;
}

int main(void)
{
  int game = 1;
  while (read_board()) {
    printf("Game #%d: ", game++);
    if (check(isblack)) {
      printf("white");
    } else if (check(iswhite)) {
      printf("black");
    } else {
      printf("no");
    }
    printf(" king is in check.\n");
  }
  return 0;
}
