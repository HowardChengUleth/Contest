#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int reverse(int n)
{
  int res = 0;
  while (n) {
    res *= 10;
    res += n % 10;
    n /= 10;
  }
  return res;
}

int rev_str(char *s, int n)
{
  int res = 0;
  int i;

  for (i = n-1; i >= 0; i--) {
    res *= 10;
    res += s[i] - '0';
  }
  return res;
}

void decode(char *line)
{
  int n = strlen(line);
  int code;

  if (!line[0]) {
    return;
  }
  assert(n >= 2);

  code = rev_str(line+n-2, 2);
  if ((65 <= code && code <= 90) ||
      (97 <= code && code <= 99) ||
      (code == 32 || code == 33 || code == 44 || code == 46 || code == 58 ||
       code == 59 || code == 63)) {
    putchar(code);
    line[n-2] = 0;
    decode(line);
  } else {
    assert(n >= 3);
    code = rev_str(line+n-3, 3);
    assert(100 <= code && code <= 122);
    putchar(code);
    line[n-3] = 0;
    decode(line);
  }
}

int main(void)
{
  char line[1000];
  int i;

  while (fgets(line, 1000, stdin)) {
    line[strlen(line)-1] = 0;

    if (isdigit(line[0])) {
      decode(line);
      printf("\n");
    } else {
      for (i = strlen(line)-1; i >= 0; i--) {
	if (line[i] < 100) {
	  printf("%02d", reverse(line[i]));
	} else {
	  printf("%03d", reverse(line[i]));
	}
      }
      printf("\n");
    }
  }
  return 0;
}
