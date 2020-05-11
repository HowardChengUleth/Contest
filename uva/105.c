/* @JUDGE_ID: 1102NT 105 C "Brute force" */

#include <stdio.h>
#include <assert.h>

#define MAX_COORD 20000

int main(void)
{
  int l, h, r;
  int skyline[MAX_COORD];
  int max_coord = 0;
  int count;
  int i, prev;
  int base;


  for (i = 0; i < MAX_COORD; i++) {
    skyline[i] = 0;
  }

  count = 0;
  while (scanf("%d %d %d", &l, &h, &r) == 3) {
    if (!count) {
      base = l;
      count = 1;
    }
    if (r > max_coord) {
      max_coord = r;
    }
    assert(h > 0);
    assert(r > l);
    for (i = l; i < r; i++) {
      if (h > skyline[i-base]) {
	skyline[i-base] = h;
      }
    }
  }

  /* print skyline */
  prev = 0;
  count = 0;
  for (i = 0; i <= max_coord-base; i++) {
    if (skyline[i] != prev) {
      if (count > 0) {
        printf(" ");
      }
      printf("%d %d", i+base, skyline[i]);
      count++;
    }
    prev = skyline[i];
  }
/*
  if (prev) {
    printf(" %d %d", max_coord, 0);
  }
*/
  printf("\n");
  return 0;
}
