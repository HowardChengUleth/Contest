/* @JUDGE_ID: 1102NT 297 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char image[32][32];

void clear_image(void)
{
  int i, j;
  for (i = 0; i < 32; i++) {
    for (j = 0; j < 32; j++) {
      image[i][j] = 0;
    }
  }
}

int count_black(void)
{
  int i, j, c;

  c = 0;
  for (i = 0; i < 32; i++) {
    for (j = 0; j < 32; j++) {
      c += image[i][j];
    }
  }
  return c;
}

char *or_image(int n, int r, int c, char *str)
{
  int i, j;
  char *p;

  if (*str == 'f') {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	image[r+i][c+j] = 1;
      }
    }
    return str+1;
  } else if (*str == 'e') {
    return str+1;
  } else {
    p = or_image(n/2, r, c, str+1);
    p = or_image(n/2, r+n/2, c, p);
    p = or_image(n/2, r, c+n/2, p);
    p = or_image(n/2, r+n/2, c+n/2, p);
    return p;
  }
}

int main(void)
{
  int cases;
  char buffer[20000];

  scanf("%d", &cases);
  while (cases-- > 0) {
    clear_image();
    scanf("%s", buffer);
    or_image(32, 0, 0, buffer);
    scanf("%s", buffer);
    or_image(32, 0, 0, buffer);
    printf("There are %d black pixels.\n", count_black());
  }
  return 0;
}
