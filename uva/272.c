/* @JUDGE_ID: 1102NT 272 C "" */

#include <stdio.h>

int main(void)
{
  int c, first;

  first = 1;
  while ((c = getchar()) != EOF) {
    if (c == '"') {
      if (first) {
	printf("``");
	first = 0;
      } else {
	printf("''");
	first = 1;
      }
    } else {
      putchar(c);
    }
  }
  return 0;
}
