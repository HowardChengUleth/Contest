/* @JUDGE_ID: 1102NT 10530 C "" */

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
  char bad[11], buffer[1024];
  int guess, i, cheat;

  memset(bad, 0, 11);
  while (scanf("%d\n", &guess) && guess > 0) {
    fgets(buffer, 1024, stdin);
    if (!strcmp(buffer, "too high\n")) {
      memset(bad+guess, 1, 10-guess+1);
    } else if (!strcmp(buffer, "too low\n")) {
      memset(bad+1, 1, guess); 
    } else {
      assert(!strcmp(buffer, "right on\n"));
      cheat = 1;
      for (i = 1; i <= 10; i++) {
	if (!bad[i]) {
	  cheat = 0;
	  break;
	}
      }
      if (cheat || bad[guess]) {
	printf("Stan is dishonest\n");
      } else {
	printf("Stan may be honest\n");
      }
      memset(bad, 0, 11);
    }

  }

  return 0;
}
