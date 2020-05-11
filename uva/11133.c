#include <stdio.h>

int ans[50];

int count(int first, int last)
{
  int total = 0;
  int i, d;

  if (ans[last] >= 0) {
    return ans[last];
  }

  if (first == last) {
    return 1;
  }

  for (i = last-1; i >= first; i--) {
    d = last - i;
    if (last % d == 0) {
      total += count(first, i);
    }
  }

  return ans[last] = total;
}

int main(void)
{
  int first, last;
  int i;

  while (scanf("%d %d", &first, &last) == 2 && first < last) {
    for (i = 0; i <= last; i++) {
      ans[i] = -1;
    }
    printf("%d %d %d\n", first, last, count(first, last));
  }

  return 0;
}
