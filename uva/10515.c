/* @JUDGE_ID: 1102NT 10515 C "" */

#include <stdio.h>
#include <string.h>

int main(void)
{
  char m[105], n[105];
  int m_val;
  int ans, t, i, j;

  while (scanf("%s %s", m, n) == 2 && (strcmp(m, "0") || strcmp(n, "0"))) {
    /* only need last digit */
    m_val = m[strlen(m)-1] - '0';

    ans = 1;
    for (i = 0; n[i]; i++) {
      /* we could have precomputed a table of a^10 %10 and a^k % 10 for k
         = 0, 1, ..., 9, but this is fast enough */ 

      t = ans;
      ans = 1;
      for (j = 0;  j < 10; j++) {
	ans = (ans * t) % 10;
      }
      for (j = 0; j < n[i] - '0'; j++) {
	ans = (ans * m_val) % 10;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
