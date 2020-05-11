/* @JUDGE_ID: 1102NT 10267 C "" */

#include <stdio.h>

char image[251][251];
int M, N;

void clear(void)
{
  int i, j;

  for (i = 1; i <= N; i++) {
    for (j = 1; j <= M; j++) {
      image[i][j] = 'O';
    }
  }
}

void create(int m, int n)
{
  M = m;
  N = n;
  clear();
}

void vdraw(int x, int y1, int y2, char C)
{
  int i;

  if (y1 > y2) {
    vdraw(x, y2, y1, C);
  } else {
    for (i = y1; i <= y2; i++) {
      image[i][x] = C;
    }
  }
}

void hdraw(int x1, int x2, int y, char C)
{
  int i;

  if (x1 > x2) {
    hdraw(x2, x1, y, C);
  } else {
    for (i = x1; i <= x2; i++) {
      image[y][i] = C;
    }
  }
}

void kdraw(int x1, int y1, int x2, int y2, char C)
{
  int i, j;

  if (x1 > x2) {
    kdraw(x2, y1, x1, y2, C);
  } else if (y1 > y2) {
    kdraw(x1, y2, x2, y1, C);
  } else {
    for (i = y1; i <= y2; i++) {
      for (j = x1; j <= x2; j++) {
	image[i][j] = C;
      }
    }
  }
}

void fill(int x, int y, char C)
{
  char t;
  
  t = image[y][x];
  if (t == C) {
    return;
  }
  image[y][x] = C;
  if (x+1 <= M && image[y][x+1] == t) {
    fill(x+1, y, C);
  }
  if (x-1 >= 1 && image[y][x-1] == t) {
    fill(x-1, y, C);
  }
  if (y+1 <= N && image[y+1][x] == t) {
    fill(x, y+1, C);
  }
  if (y-1 >= 0 && image[y-1][x] == t) {
    fill(x, y-1, C);
  }
}

void S(char *name)
{
  int i, j;
  
  printf("%s\n", name);
  for (i = 1; i <= N; i++) {
    for (j = 1; j <= M; j++) {
      printf("%c", image[i][j]);
    }
    printf("\n");
  }
}

int main(void)
{
  char buffer[10240], name[10240];
  char C;
  int m, n, x1, x2, y1, y2, x, y;

  while (1) {
    fgets(buffer, 10240, stdin);
    if (buffer[0] == 'X') {
      break;
    }
    switch (buffer[0]) {
      case 'I':
	sscanf(buffer, "%*c %d %d", &m, &n);
	create(m, n);
	break;
      case 'C':
	clear();
	break;
      case 'L':
	sscanf(buffer, "%*c %d %d %c", &x, &y, &C);
	image[y][x] = C;
	break;
      case 'V':
	sscanf(buffer, "%*c %d %d %d %c", &x, &y1, &y2, &C);
	vdraw(x, y1, y2, C);
	break;
      case 'H':
	sscanf(buffer, "%*c %d %d %d %c", &x1, &x2, &y, &C);
	hdraw(x1, x2, y, C);
	break;
      case 'K':
	sscanf(buffer, "%*c %d %d %d %d %c", &x1, &y1, &x2, &y2, &C);
	kdraw(x1, y1, x2, y2, C);
	break;
      case 'F':
	sscanf(buffer, "%*c %d %d %c", &x, &y, &C);
	fill(x, y, C);
	break;
      case 'S':
	sscanf(buffer, "%*c %s", name);
	S(name);
	break;
    }
  }
  return 0;
}
