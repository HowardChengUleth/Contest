/* @JUDGE_ID: 1102NT 10082 C "" */

#include <stdio.h>

char *keyboard[4] = {
  "`1234567890-=",
  "QWERTYUIOP[]\\",
  "ASDFGHJKL;'",
  "ZXCVBNM,./"
};

char lookup(char c)
{
  int i, j;

  for (i = 0; i < 4; i++) {
    for (j = 1; keyboard[i][j]; j++) {
      if (keyboard[i][j] == c) {
	return keyboard[i][j-1];
      }
    }
  }
  return c; 
}

int main(void)
{
  int c;

  while ((c = getchar()) != EOF) {
    putchar(lookup(c));
  }
  return 0;
}

