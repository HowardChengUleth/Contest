#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

char dir_name[5] = "NESW";
int offset_x[4] = {0, 1, 0, -1};
int offset_y[4] = {1, 0, -1, 0};

int left(int dir)
{
  return (dir + 3) % 4;
}

int right(int dir)
{
  return (dir + 1) % 4;
}

char scent[51][51];
int m, n;
int x, y, dir;

int move(void)
{
  int new_x = x + offset_x[dir];
  int new_y = y + offset_y[dir];

  if (0 <= new_x && 0 <= new_y && new_x <= m && new_y <= n) {
    x = new_x;
    y = new_y;
    return 0;
  }
  
  if (scent[x][y]) {
    /* ignore move */
    return 0;
  } else {
    scent[x][y] = 1;
    return 1;
  }
}

void process(char *buffer)
{
  int len = strlen(buffer);
  int i;
  int lost = 0;

  for (i = 0; i < len && !lost; i++) {
    switch (buffer[i]) {
    case 'L':
      dir = left(dir);
      break;
    case 'R':
      dir = right(dir);
      break;
    case 'F':
      lost = move();
      break;
    default:
      fprintf(stderr, "Process: in trouble\n");
      exit(1);
    }
  }

  printf("%d %d %c", x, y, dir_name[dir]);
  if (lost) {
    printf(" LOST");
  }
  printf("\n");  
}

int main(void)
{
  int i, j;
  char buffer[1024];

  /* clear scent */
  for (i = 0; i < 51; i++) {
    for (j = 0; j < 51; j++) {
      scent[i][j] = 0;
    }
  }
  scanf("%d %d", &m, &n);
  while (scanf("%d %d %s", &x, &y, buffer) == 3) {
    switch (buffer[0]) {
    case 'N':
      dir = NORTH;
      break;
    case 'E':
      dir = EAST;
      break;
    case 'S':
      dir = SOUTH;
      break;
    case 'W':
      dir = WEST;
      break;
    default:
      fprintf(stderr, "we are in trouble.\n");
      exit(1);
    }
    scanf("%s", buffer);
    process(buffer);
  }
  return 0;
}
