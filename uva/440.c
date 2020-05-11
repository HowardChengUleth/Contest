/* @JUDGE_ID: 1102NT 440 C "" */

#include <stdio.h>
#include <assert.h>

int get_next(int *used, int n, int m, int curr)
{
  int p;
  
  p = curr;
  while (m > 0) {
    if (++p == n) {
      p = 0;
    }
    if (!used[p]) {
      m--;
    }
  }
  return p;
}

int works(int n, int m)
{
  int used[150];
  int curr, i, killed;

  for (i = 0; i < 150; i++) {
    used[i] = 0;
  }

  curr = 0;
  killed = 1;
  used[curr] = 1;

  while (curr != 1) {
    curr = get_next(used, n, m, curr);
    assert(!used[curr]);
    killed++;
    used[curr] = 1;
  }
  return (killed == n);
}

int main(void)
{
  int n, m, done;

  while (scanf("%d", &n) == 1 && n > 0) {
    done = 0;
    for (m = 2; !done; m++) {
      if (works(n, m)) {
	done = 1;
	printf("%d\n", m);
      }  
    }
  }
  return 0;
}
