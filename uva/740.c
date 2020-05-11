#include <stdio.h>
#include <string.h>

int main(void)
{
  char table[2][34];
  char message[100];
  int row, i, j, index;
  int n;

  fgets(table[0], 34, stdin);
  fgets(table[1], 34, stdin);

  while (scanf("%s", message) == 1) {
    row = 0;
    n = strlen(message);
    for (i = 0; i < n; i += 5) {
      index = 0;
      for (j = 0; j < 5; j++) {
	index *= 2;
	index += message[i+j] - '0';
      }
      if (index == 27) {
	row = 0;
      } else if (index == 31) {
	row = 1;
      } else {
	putchar(table[row][index]);
      }
    }
    printf("\n");
  }

  return 0;
}
