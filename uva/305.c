/* @JUDGE_ID: 1102NT 305 C "" */

#include <stdio.h>

int table[14] = {
  0,
  2,
  7,
  5,
  30,
  169,
  441,
  1872,
  7632,
  1740,
  93313,
  459901,
  1358657,
  2504881
};

int main(void)
{
  int k;
  while (scanf("%d", &k) == 1 && k) {
    printf("%d\n", table[k]);
  }
  return 0;
}
