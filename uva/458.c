/* @JUDGE_ID: 1102NT 458 C "" */

#include <stdio.h>

int main(void)
{
  int c;
  
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      putchar(c);
    } else {
      putchar(c-7);
    }
  }
  return 0;
}
