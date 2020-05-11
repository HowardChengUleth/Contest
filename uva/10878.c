#include <stdio.h>

int main(void)
{
  char line[100];
  int pos[7] = { 9, 8, 7, 5, 4, 3, 2 };
  int ascii;
  int i;

  while (fgets(line, 100, stdin)) {
    if (line[0] != '|') continue;
    ascii = 0;
    for (i = 0; i < 7; i++) {
      ascii += ((line[pos[i]] == 'o') ? 1 : 0) << i;
    }
    putchar(ascii);
  }
  return 0;
}
