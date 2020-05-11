#include <stdio.h>
#include <string.h>

int main(void)
{
  char line[101][102];
  int i, j, k;
  int len[101];
  int n, maxlen;

  n = 0;
  while (fgets(line[n], 102, stdin)) {
    line[n][strlen(line[n])-1] = 0;     /* get rid of '\n' */
    len[n] = strlen(line[n]);
    n++;
  }

  maxlen = 0;
  for (i = 0; i < n; i++) {
    if (len[i] > maxlen) {
      maxlen = len[i];
    }
    for (j = i+1; j < n; j++) {
      if (len[j] < len[i]) {
	for (k = 0; k < len[i]-len[j]; k++) {
	  line[j][len[j]+k] = ' ';
	}
	line[j][len[i]] = 0;
	len[j] = len[i];
      }
    }
  }

  for (i = 0; i < maxlen; i++) {
    for (j = n; j >= 0; j--) {
      if (i < len[j]) {
	putchar(line[j][i]);
      }
    }
    putchar('\n');
  }
  return 0;
}
