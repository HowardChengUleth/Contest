/* @JUDGE_ID: 1102NT 10551 C "" */

#include <stdio.h>

int main(void)
{
  char p[1001], m_str[10], r_str[10];
  int b;
  long long m, r;
  int i;

  while (scanf("%d", &b) == 1 && b > 0) {
    scanf("%s %s", p, m_str);
    
    m = 0;
    for (i = 0; m_str[i]; i++) {
      m = b*m + (m_str[i]-'0');
    }

    r = 0;
    for (i = 0; p[i]; i++) {
      r = (b*r + (p[i]-'0')) % m;
    }

    i = 0;
    r_str[i++] = (r % b) + '0';
    r /= b;
    while (r) {
      r_str[i++] = (r % b) + '0';
      r /= b;
    }
    while (i > 0) {
      putchar(r_str[--i]);
    }
    putchar('\n');
  }
  return 0;
}
