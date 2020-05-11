#include <stdio.h>
#include <string.h>

int main(void)
{
  char str[101];
  int G, n;
  int i, j;

  while (scanf("%d", &G) == 1 && G) {
    scanf("%s", str);
    n = strlen(str);
    for (i = 0; i < n; i += n/G) {
      for (j = n/G-1; j >= 0; j--) {
	putchar(str[i+j]);
      }
    }
    putchar('\n');
  }

  return 0;
}
