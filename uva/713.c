/* @JUDGE_ID: 1102NT 713 C "" */

#include <stdio.h>
#include <string.h>

void reverse(char *s)
{
  char t;
  int i, n;

  n = strlen(s);
  for (i = 0; i < n/2; i++) {
    t = s[i];
    s[i] = s[n-1-i];
    s[n-1-i] = t;
  }
}

void add(char *a, char *b, char *c)
{
  int i, carry, sum;
  int adone, bdone;

  adone = bdone = 0;
  carry = 0;
  for (i = 0; !adone || !bdone; i++) {
    sum = carry;
    if (!adone && a[i]) {
      sum += a[i] - '0';
    } else {
      adone = 1;
    }
    if (!bdone && b[i]) {
      sum += b[i] - '0';
    } else {
      bdone = 1;
    }
    if (adone && bdone) {
      break;
    }
    c[i] = sum % 10 + '0';
    carry = sum >= 10;
  }
  if (carry) {
    c[i++] = '1';
  }
  c[i] = 0;
}

int main(void)
{
  int cases;
  char a[201], b[201], c[202];
  int i;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%s %s", a, b);
    add(a, b, c);
    for (i = 0; c[i] == '0'; i++)
      ;
    printf("%s\n", c+i);
  }
  return 0;
}
