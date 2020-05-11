/* @JUDGE_ID: 1102NT 10035 C "" */

#include <stdio.h>
#include <string.h>

int main(void)
{
  char str1[11], str2[11];
  int n1[13], n2[13];
  int i, j, c, nc;

  while (1) {
    scanf("%s %s", str1, str2);
    if (!strcmp(str1, "0") && !strcmp(str2, "0")) {
      break;
    }
    for (i = 0; i < 13; i++) {
      n1[i] = n2[i] = 0;
    }
    j = 0;
    for (i = strlen(str1)-1; i >= 0; i--) {
      n1[j++] = str1[i] - '0';
    }
    j = 0;
    for (i = strlen(str2)-1; i >= 0; i--) {
      n2[j++] = str2[i] - '0';
    }

    c = nc = 0;
    for (i = 0; i < 13; i++) {
      c = (c + n1[i] + n2[i] > 9);
      if (c) nc++;
    }

    if (nc == 0) {
      printf("No carry operation.\n");
    } else if (nc == 1) {
      printf("1 carry operation.\n");
    } else {
      printf("%d carry operations.\n", nc);
    }
  }
  return 0;
}
