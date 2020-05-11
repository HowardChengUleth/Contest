/* @JUDGE_ID: 1102NT 587 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


int main(void)
{
  char buffer[10240], *ptr, *p2;
  int case_num = 1;
  double x, y, t;
  int dx, dy;

  while (fgets(buffer, 10240, stdin) && strcmp(buffer, "END\n")) {
    printf("Map #%d\n", case_num++);
    x = y = 0;
    ptr = buffer;
    while (ptr = strtok(ptr, ",.\n")) {
      dx = dy = 0;
      t = strtol(ptr, &p2, 10);
      for (; *p2; p2++) {
	switch (*p2) {
	case 'N':
	  dy = 1;
	  break;
	case 'S':
	  dy = -1;
	  break;
	case 'E':
	  dx = 1;
	  break;
	case 'W':
	  dx = -1;
	  break;
	default:
	  assert(0);
	}
      }
      if (dx && dy) {
	t /= sqrt(2);
      }
      x += t*dx;
      y += t*dy;
      ptr = 0;
    }

    printf("The treasure is located at (%.3f,%.3f).\n", x, y);
    printf("The distance to the treasure is %.3f.\n", sqrt(x*x+y*y));
    printf("\n");
  }
  return 0;
}
