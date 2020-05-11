/* @JUDGE_ID: 1102NT 10098 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void permutations(char *perm, int n, int index)
{
  int i;
  char t, prev;
  
  if (index == n) {
    printf("%s\n", perm);
    return;
  }
  prev = 0;
  for (i = index; i < n; i++) {
    permutations(perm, n, index+1);
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

int cmp(const void *a, const void *b)
{
  return (int)(*(char *)a) - (int)(*(char *)b);
}

int main(void)
{
  char s[100];
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%s", s);
    qsort(s, strlen(s), 1, cmp);
    permutations(s, strlen(s), 0);
    printf("\n");
  }
  return 0;
}

