/* @JUDGE_ID: 1102NT 10324 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
  char buffer[1000002], buf2[1000];
  int n, i, j, cases, t, l;
  int count[1000002];

  cases = 1;
  while (fgets(buffer, 1000002, stdin) && buffer[0] != '\n') {
    count[0] = buffer[0] - '0';
    l = strlen(buffer)-1;
    for (i = 1; i < l; i++) {
      count[i] = count[i-1] + (buffer[i] - '0');
    }
    printf("Case %d:\n", cases++);
    fgets(buf2, 1000, stdin);
    sscanf(buf2, "%d", &n);
    while (n-- > 0) {
      fgets(buf2, 1000, stdin);
      sscanf(buf2, "%d %d", &i, &j);
      if (i > j) {
	t = i;
	i = j;
	j = t;
      }
      assert(0 <= i && j < l);
      if ((buffer[i] == '0' && count[i] == count[j]) ||
	  (buffer[i] == '1' && count[j] - count[i] == j - i)) {
	printf("Yes\n");
      } else {
	printf("No\n");
      }
    }
  }
  return 0;
}
