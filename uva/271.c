#include <stdio.h>
#include <string.h>

int good(char *s, int n)
{
  int count = 0;
  int i;

  /* start from the end, counting the number of correct sentences concatenated
     together at any stage */

  for (i = n-1; i >= 0; i--) {
    if ('p' <= s[i] && s[i] <= 'z') {
      count++;      /* we have one more correct sentences */
    } else if (s[i] == 'N') {
      /* doesn't change the count, as long as there is something after that */
      if (count < 1) {
	return 0;
      }
    } else if (strchr("CDEI", s[i])) {
      /* reduce count by 1, as long as there are two sentences after that */
      if (count < 2) {
	return 0;
      }
      count--;
    }
  }
  return count == 1;

}

int main(void)
{
  char s[1000];

  while (scanf("%s", s) == 1) {
    printf("%s\n", (good(s, strlen(s)) ? "YES" : "NO"));
  }
  return 0;
}
