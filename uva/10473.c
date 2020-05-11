/* @JUDGE_ID: 1102NT 10473 C "" */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char str[10000];
  int x;

  while (scanf("%s", str) == 1) {
    if (str[0] == '-') break;
    if (strstr(str, "0x") == str) {
      sscanf(str, "%x", &x);
      printf("%d\n", x);
    } else {
      sscanf(str, "%d", &x);
      printf("0x%X\n", x);
    }
  }

  return 0;
}
