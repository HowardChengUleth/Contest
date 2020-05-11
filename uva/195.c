/* @JUDGE_ID: 1102NT 195 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cmp(const void *a, const void *b)
{
  char *x = (char *)a, *y = (char *)b;

  if (toupper(*x) != toupper(*y)) {
    return toupper(*x) - toupper(*y);
  } else if (!isupper(*x) && isupper(*y)) {
    return 1;
  } else {
    return -1;
  }
}

void permute(char *perm, int n, int index)
{
  int i;
  char t;
  
  if (index == n) {
    printf("%s\n", perm);
    return;
  }
  for (i = index; i < n; i++) {
    permute(perm, n, index+1);
    for ( ; i < n-1 && perm[index] == perm[i+1]; i++) ;
    if (i < n-1) {
      t = perm[index];
      perm[index] = perm[i+1];
      perm[i+1] = t;
    }
  }
  t = perm[index];
  for (i = index; i < n-1; i++) {
    perm[i] = perm[i+1];
  }
  perm[n-1] = t;
}

int main(void)
{
  char s[1024];
  int n;

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%s", s);
    qsort(s, strlen(s), 1, cmp);
    permute(s, strlen(s), 0);
  }
  return 0;
}
