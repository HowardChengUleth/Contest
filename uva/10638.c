/* @JUDGE_ID: 1102NT 10638 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int amount[10];
int n;
int best;

void search(int *final, int from, int to, int so_far)
{
  int a, b, pay;

  if (best != -1 && so_far >= best) {
    return; 
  }

  if (from >= n) {
    /* we are done */
    if (best == -1 || so_far < best) {
      best = so_far;
    }
    return;
  }

  if (to >= n) {
    /* from finished paying */
    if (amount[from] == final[from]) {
      search(final, from+1, 0, so_far);
    }
    return;
  }
    
  if (from == to) {
    search(final, from, from+1, so_far);
    return;
  }

  if (amount[from] >= final[from]) {
    /* no need to pay */
    search(final, from+1, 0, so_far);
    return;
  }

  if (amount[to] <= final[to]) {
    /* don't have to pay "to" */
    search(final, from, to+1, so_far);
    return;
  }

  /* after all this, we try to pay */
  a = final[from] - amount[from];
  b = amount[to] - final[to];
  pay = (a < b) ? a : b;        /* amount "from" pays to "to" */
  amount[from] += pay;
  amount[to] -= pay;
  search(final, from, to+1, so_far+1);
  amount[from] -= pay;
  amount[to] += pay;

  /* or we try not to pay him */
  search(final, from, to+1, so_far);
}

/* go through C(n,k) ways of distributing extra penny */
void choose(int n, int k, int *final)
{
  if (k == 0) {
    search(final, 0, 0, 0);
  } else if (n >= k) {
    final[n-1]++;
    choose(n-1, k-1, final);
    final[n-1]--;
    choose(n-1, k, final);
  }
}

int main(void)
{
  double t;
  int i;
  int total;
  int rem;
  int final[10];

  while (scanf("%d", &n) == 1 && n > 0) {
    total = 0;
    for (i = 0; i < n; i++) {
      scanf("%lf", &t);
      amount[i] = (int)(t*100+0.5);
      total += amount[i];
    }
    rem = total % n; 
    for (i = 0; i < n; i++) {
      final[i] = total/n;
    }
    best = -1;
    choose(n, rem, final);
    printf("%d\n", best);
  }

  return 0;
}
