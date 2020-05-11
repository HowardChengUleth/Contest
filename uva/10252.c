#include <stdio.h>

int main(void)
{
  char s1[1002], s2[1002];
  int c1[26], c2[26], i, j;

  while (fgets(s1, 1002, stdin)) {
    fgets(s2, 1002, stdin);
    for (i = 0; i < 26; i++) {
      c1[i] = c2[i] = 0;
    }
    for (i = 0; s1[i] != '\n'; i++) {
      c1[s1[i]-'a']++;
    }
    for (i = 0; s2[i] != '\n'; i++) {
      c2[s2[i]-'a']++;
    }
    for (i = 0; i < 26; i++) {
      for (j = 0; j < c1[i] && j < c2[i]; j++) {
	putchar(i+'a');
      }
    }
    putchar('\n');

  }
  return 0;
}
