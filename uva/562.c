/* @JUDGE_ID: 1102NT 562 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int coin[100], n;

int do_case(void)
{
  char table[50001], temp[50001];
  int i, j, t1, t2;

  memset(table, 0, 50001);
  table[0] = 1;
  for (i = 0; i < n; i++) {
    memset(temp, 0, 50001);
    for (j = 0; j < 50001; j++) {
      if (table[j]) {
	t1 = j + coin[i];
	t2 = j - coin[i];
	if (t2 < 0) {
	  t2 *= -1;
	}
	assert(0 <= t1 && t1 < 50001 && 0 <= t2 && t2 < 50001);
	temp[t1] = temp[t2] = 1;
      }
    }
    memcpy(table, temp, 50001);
  }

  for (i = 0; i < 50001; i++) {
    if (table[i]) {
      return i;
    }
  }
  assert(0);
}

int main(void)
{
  int N, i;
  
  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      scanf("%d", coin+i);
    }
    printf("%d\n", do_case());
  }

  return 0;
}
