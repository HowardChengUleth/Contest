/* @JUDGE_ID: 1102NT 729 C "" */

#include <stdio.h>

void comb(char *string, int n, int h, int index)
{
  int i;
  
  if (n == h) {
    for (i = index; i < index + n; i++) {
      string[i] = '1';
    }
    printf("%s\n", string);
  } else if (h == 0) {
    for (i = index; i < index + n; i++) {
      string[i] = '0';
    }
    printf("%s\n", string);
  } else {
    string[index] = '0';
    comb(string, n-1, h, index+1);
    string[index] = '1';
    comb(string, n-1, h-1, index+1);
  }
}

int main(void)
{
  int cases, n, h;
  char string[100];
  
  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &n, &h);
    string[n] = 0;
    comb(string, n, h, 0);
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
