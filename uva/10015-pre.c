#include <stdio.h>
#include <assert.h>

int prime[3502];

int ans[3502];

int isprime(int n)
{
  int k;

  /* known to be odd */
  for (k = 3; k*k <= n; k += 2) {
    if (n % k == 0) {
      return 0;
    }
  }
  return 1;
}

int solve(int n)
{
  char killed[3501];
  int num_killed = 0;
  int i, p, c;

  for (i = 0; i < n; i++) {
    killed[i] = 0;
  }
  
  i = 0;
  p = 0;
  while (num_killed < n-1) {
    c = (killed[i]) ? 0 : 1;
    while (c < prime[p]) {
      i = (i+1) % n;
      if (!killed[i]) {
	c++;
      }
    }
    killed[i] = 1;
    p++;
    num_killed++;
  }
  
  for (i = 0; i < n; i++) {
    if (!killed[i]) {
      return i+1;
    }
  }
  assert(0);
  return -1;
}

int main(void)
{
  int n;
  int p, i;

  prime[0] = 2;
  p = 3;
  for (i = 1; i < 3502; i++) {
    while (!isprime(p)) p += 2;
    prime[i] = p;
    p += 2;
  }

  printf("int ans[3502] = {\n");
  printf("1,\n1,\n");
  ans[1] = 1;
  ans[2] = 1;
  for (n = 3; n < 3501; n++) {
    ans[n] = solve(n);
    printf("%d,\n", ans[n]);
  }
  ans[3501] = solve(3501);
  printf("%d};\n", ans[3501]);

  /*
  while (scanf("%d", &n) == 1 && n) {
    printf("%d\n", ans[n]);
  }
  */
  return 0;
}
