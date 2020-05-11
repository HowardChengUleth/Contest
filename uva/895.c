/* @JUDGE_ID: 1102NT 895 C "" */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int freq[1000][26];
int n;

int main(void)
{
  char buffer[1024];
  char *p;
  int count, i, j, f[26];

  while (scanf("%s\n", buffer) == 1 && strcmp(buffer, "#")) {
    for (p = buffer; *p; p++) {
      freq[n][*p-'a']++;
    }
    n++;
  }
  while (fgets(buffer, 1024, stdin) && buffer[0] != '#') {
    for (i = 0; i < 26; i++) {
      f[i] = 0;
    }
    for (p = buffer; *p; p++) {
      if (islower(*p)) {
	f[*p-'a']++;
      }
    }
    count = 0;
    for (i = 0; i < n; i++) {
      for (j = 0; j < 26; j++) {
	if (freq[i][j] > f[j]) break;
      }
      if (j >= 26) {
	count++;
      }
    }
    printf("%d\n", count);

  }
  return 0;
}
