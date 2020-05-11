#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b)
{
  char *s1 = *(char **)a, *s2 = *(char **)b;
  char t1[1024], t2[1024];
  
  strcpy(t1, s1);
  strcat(t1, s2);
  strcpy(t2, s2);
  strcat(t2, s1);
  return strcmp(t2, t1);
}

int main(void)
{
  int N, i;
  char *num[50];
  
  for (i = 0; i < 50; i++) {
    num[i] = malloc(1024);
  }
  while (scanf("%d", &N) == 1 && N) {
    for (i = 0; i < N; i++) {
      scanf("%s", num[i]);
    }
    qsort(num, N, sizeof(*num), cmp);
    for (i = 0; i < N; i++) {
      printf("%s", num[i]);
    }
    printf("\n");
  }
  for (i = 0; i < 50; i++) {
    free(num[i]);
  }
  return 0;
}
