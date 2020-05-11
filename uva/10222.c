/* @JUDGE_ID: 1102NT 10222 C "" */

#include <stdio.h>
#include <ctype.h>

char *keyboard[4] = {
  "`1234567890-=",
  "QWERTYUIOP[]\\",
  "ASDFGHJKL;'",
  "ZXCVBNM,./"
};

char lookup(char c)
{
  int i, j;
  
  c = toupper(c);

  for (i = 0; i < 4; i++) {
    for (j = 1; keyboard[i][j]; j++) {
      if (keyboard[i][j] == c) {
	return tolower(keyboard[i][j-1]);
      }
    }
  }
  return c; 
}

int main(void)
{
  int c;

  while ((c = getchar()) != EOF) {
    putchar(lookup(lookup(c)));
  }
  return 0;
}

