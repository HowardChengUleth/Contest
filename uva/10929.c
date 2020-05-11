#include <stdio.h>
#include <string.h>

int main(void)
{
  char s[1024];
  int sum = 0;
  int i;

  while (scanf("%s", s) == 1 && strcmp(s, "0")) {
    sum = 0;
    for (i = 0; s[i]; i++) {
      sum = (10 * sum + s[i] - '0') % 11;
    }
    printf("%s is %s multiple of 11.\n", s, sum ? "not a" : "a");

  }
  return 0;
}
  
