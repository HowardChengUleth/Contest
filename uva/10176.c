#include <stdio.h>
#include <ctype.h>

const int p = 131071;

int getnonspace(void)
{
  int c;

  while ((c = getchar()) != EOF) {
    if (!isspace(c)) return c;
  }
  return EOF;
}

int main(void)
{
  int c;
  int n;

  while ((c = getnonspace()) != EOF) {
    n = 0;
    while (c != '#') {
      n = (n * 2) % p;
      if (c == '1') {
	if (++n == p) {
	  n = 0;
	}
      }
      c = getnonspace();
    }
    printf("%s\n", (n ? "NO" : "YES"));
  }

  return 0;
}
