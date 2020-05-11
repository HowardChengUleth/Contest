#include <stdio.h>
#include <ctype.h>

int convert(char *s, int b)
{
  int val = 0;
  int d;

  while (*s) {
    if (isdigit(*s)) {
      d = *s - '0';
    } else {
      d = *s - 'A' + 10;
    }
    if (d >= b) {
      return -1;
    }
    val = val * b + d;
    s++;
  }
  return val;
}

int main(void)
{
  char str1[100], str2[100];
  int b1, b2, found;
  int X, Y;

  while (scanf("%s %s", str1, str2) == 2) {
    found = 0;
    for (b1 = 2; b1 <= 36 && !found; b1++) {
      X = convert(str1, b1);
      if (X < 0) continue;
      for (b2 = 2; b2 <= 36 && !found; b2++) {
	Y = convert(str2, b2);
	if (Y < 0) continue;
	if (X == Y) {
	  printf("%s (base %d) = %s (base %d)\n", str1, b1, str2, b2);
	  found = 1;
	}
      }
    }
    if (!found) {
      printf("%s is not equal to %s in any base 2..36\n", str1, str2);
    }
  }
  return 0;
}
