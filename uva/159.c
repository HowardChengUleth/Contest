#include <stdio.h>
#include <string.h>

int main(void)
{
  char word[4][11], *p;
  int index[4];
  int i, j, k;
  int first = 1;
  int center;

  while (scanf("%s", word[0]) == 1 && word[0][0] != '#') {
    scanf("%s %s %s", word[1], word[2], word[3]);

    for (i = 0; i < 4; i++) {
      index[i] = -1;
    }

    for (i = 0; i < 4; i+=2) {
      for (j = 0; word[i][j]; j++) {
	if (p = strchr(word[i+1], word[i][j])) {
	  index[i] = j;
	  index[i+1] = p - word[i+1];
	  break;
	}
      }
    }

    if (!first) {
      printf("\n");
    }
    first = 0;

    if (index[0] == -1 || index[2] == -1) {
      printf("Unable to make two crosses\n");
      continue;
    }

    center = (index[1] > index[3]) ? index[1] : index[3];
    for (i = 0; i < center + strlen(word[1]) - index[1] ||
	   i < center + strlen(word[3]) - index[3]; i++) {
      
      if (i == center) {
	printf("%s   %s\n", word[0], word[2]);
	continue;
      }

      for (k = 0; k < index[0]; k++) {
	putchar(' ');
      }
      j = index[1] + i - center;
      if (0 <= j && j < strlen(word[1])) {
	putchar(word[1][j]);
      } else {
	putchar(' ');
      }

      j = index[3] + i - center;
      if (0 <= j && j < strlen(word[3])) {
	for (k = 0; k < strlen(word[0])-index[0]-1 + 3 + index[2]; k++) {
	  putchar(' ');
	}
	putchar(word[3][j]);
      }


      printf("\n");
      
    }

    
  }
  return 0;
}
