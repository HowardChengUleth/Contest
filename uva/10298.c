/* @JUDGE_ID: 1102NT 10298 C "" */

#include <stdio.h>
#include <string.h>

int main(void)
{
  char s[1000001];
  int len, i, k, j;
  char mismatch;

  while (scanf("%s", s) == 1 && s[0] != '.') {
    len = strlen(s);
    for (k = 1; k <= len/2; k++) {
      if (len % k) continue;
      mismatch = 0;
      for (i = 0; i < k && !mismatch; i++) {
	for (j = k+i; j < len && !mismatch; j += k) {
	  if (s[i] != s[j]) {
	    mismatch = 1;
	  }
	}
      }
      if (!mismatch) {
	break;
      }
    }
    printf("%d\n", len / k);
  }
  return 0;
}
