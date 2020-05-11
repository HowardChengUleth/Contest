/* @JUDGE_ID: 1102NT 483 C "" */

#include <stdio.h>
#include <string.h>

void revprint(char *s, int len)
{
  int i;
  for (i = len-1; i >= 0; i--) {
    putchar(s[i]);
  }
}

int main(void)
{
  char line[1024], *p, *q;

  while (fgets(line, 1024, stdin)) {
    q = line;
    while (*q && isspace(*q)) {
      putchar(*q++);
    }
    p = q;
    while (*p) {
      while (*q && !isspace(*q)) {
	q++;
      }
      revprint(p, q-p);
      while (*q && isspace(*q)) {
	putchar(*q++);
      }
      p = q;
    }
  }
  return 0;
}
