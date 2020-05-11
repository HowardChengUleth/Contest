#include <stdio.h>
#include <ctype.h>

int main(void)
{
  int c;
  int sum = 0;

  while ((c = getchar()) != EOF) {
    if (isdigit(c)) {
      sum += c - '0';
    } else if (c == '!' || c == '\n') {
      putchar('\n');     /* this should take care of blank lines too */
    } else {
      while (sum > 0) {
	putchar((c == 'b') ? ' ' : c);
	sum--;
      }
    }
  }
  return 0;
}
