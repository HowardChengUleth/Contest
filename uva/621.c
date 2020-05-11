/* @JUDGE_ID: 1102NT 621 C "" */

#include <stdio.h>
#include <string.h>

char *result[4] = {"+", "-", "*", "?"};

enum { POS, NEG, FAIL, INCOMPLETE, BAD };

int decode(char *s, int len)
{
  if (len == 1 && s[0] == '1' ||
      len == 1 && s[0] == '4' ||
      len == 2 && s[0] == '7' && s[1] == '8') {
    return POS;
  }

  if (len >= 3 && s[len-2] == '3' && s[len-1] == '5' &&
      decode(s, len-2) != BAD) {
    return NEG;
  }

  if (len >= 3 && s[0] == '9' && s[len-1] == '4' &&
      decode(s+1, len-2) != BAD) {
    return FAIL;
  }

  if (len >= 4 && s[0] == '1' && s[1] == '9' && s[2] == '0' &&
      decode(s+3, len-3) != BAD) {
    return INCOMPLETE;
  }

  return BAD;
}

int main(void)
{
  int n;
  char s[10000];

  scanf("%d\n", &n);
  while (n-- > 0) {
    scanf("%s", s);

    /* last line of judge output does not end with newline */
    printf("%s%s", result[decode(s, strlen(s))], (n ? "\n" : ""));
  }
  return 0;
}
