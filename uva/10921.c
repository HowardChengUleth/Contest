#include <stdio.h>

char *strings[10] = {
  "",
  "",
  "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"
};

char map[256];

int main(void)
{
  int i, j, c;

  for (i = 0; i < 256; i++) {
    map[i] = i;
  }
  for (i = 0; i < 10; i++) {
    for (j = 0; strings[i][j]; j++) {
      map[strings[i][j]] = i + '0';
    }
  }

  while ((c = getchar()) != EOF) {
    putchar(map[c]);
  }
  return 0;
}
