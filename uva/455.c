/* @JUDGE_ID: 1102NT 455 C "" */

#include <stdio.h>
#include <string.h>

void solve_case(void)
{
  char s[100];
  int len, i, k, j;
  char mismatch = 1;

  scanf("%s", s);
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
  if (mismatch) {
    printf("%d\n", len);
  } else {
    printf("%d\n", k);
  }
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
