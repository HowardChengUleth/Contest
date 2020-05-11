/* @JUDGE_ID: 1102NT 142 C "" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point tl;
    Point br;
} Rect;

int num_i, num_r;

Point icon[50];
Rect rect[25];
char obscured[50];

void comp_obscured(void)
{
  int i, j;
  
  for (i = 0; i < num_i; i++) {
    obscured[i] = 0;
    for (j = 0; j < num_r; j++) {
      if (rect[j].tl.x <= icon[i].x && icon[i].x <= rect[j].br.x &&
	  rect[j].tl.y <= icon[i].y && icon[i].y <= rect[j].br.y) {
	obscured[i] = 1;
      }
    }
  }
}

void do_point(int x, int y)
{
  int i, d, best_d, r_index;
  int found = 0;
  
  comp_obscured();
  
  for (i = 0; i < num_r; i++) {
    if (rect[i].tl.x <= x && x <= rect[i].br.x &&
	rect[i].tl.y <= y && y <= rect[i].br.y) {
      r_index = i;
      found = 1;
    }
  }
  if (found) {
    printf("%c\n", 'A'+r_index);
    return;
  }
  best_d = 1000000;
  for (i = 0; i < num_i; i++) {
    if (obscured[i]) continue;
    d = (icon[i].x-x)*(icon[i].x-x) + (icon[i].y-y)*(icon[i].y-y);
    if (d < best_d) {
      best_d = d;
    }
  }
  for (i = 0; i < num_i; i++) {
    if (obscured[i]) continue;
    d = (icon[i].x-x)*(icon[i].x-x) + (icon[i].y-y)*(icon[i].y-y);
    if (d == best_d) {
      printf("%3d", i+1);
    }
  }
  printf("\n");  
}

void main(void)
{
  char buffer[1024];
  int x, y;
  int i;
  
  num_i = num_r = 0;
  
  while (scanf("%s", buffer) == 1 && strcmp(buffer, "#")) {
    switch (buffer[0]) {
    case 'I':
      scanf("%d %d", &(icon[num_i].x), &(icon[num_i].y));
      num_i++;
      break;
    case 'R':
      scanf("%d %d %d %d", &(rect[num_r].tl.x), &(rect[num_r].tl.y),
	    &(rect[num_r].br.x), &(rect[num_r].br.y));
      num_r++;
      break;
    case 'M':
      scanf("%d %d", &x, &y);
      do_point(x, y);
      break;
    default:
      assert(0);
    }
  } 
}
