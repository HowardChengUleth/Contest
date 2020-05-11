/* @JUDGE_ID: 1102NT 642 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char dict[100][7];
int num = 0;

int cmp(const void *a, const void *b)
{
  return *(char *)a - *(char *)b;
}

int match(char *s1, char *s2)
{
  char temp1[10], temp2[10];
  int n1, n2;

  n1 = strlen(s1);
  n2 = strlen(s2);
  if (n1 != n2) {
    return 0;
  }
  
  strcpy(temp1, s1);
  strcpy(temp2, s2);
  qsort(temp1, n1, 1, cmp);
  qsort(temp2, n2, 1, cmp);
  return !strcmp(temp1, temp2);
}

int main(void)
{
  char buffer[1024];
  int i, count;

  while (scanf("%s", buffer) == 1 && strcmp(buffer, "XXXXXX")) {
    strcpy(dict[num++], buffer);
  }
  qsort(dict, num, 7, (int (*)(const void *, const void *))strcmp);
  
  while (scanf("%s", buffer) == 1 && strcmp(buffer, "XXXXXX")) {
    count = 0;
    for (i = 0; i < num; i++) {
      if (match(buffer, dict[i])) {
	printf("%s\n", dict[i]);
	count++;
      }
    }
    if (!count) {
      printf("NOT A VALID WORD\n");
    }
    printf("******\n");
  }
  return 0;
}
