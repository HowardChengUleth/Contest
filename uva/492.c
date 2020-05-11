#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  int c;
  int inword = 0;
  int cons = 0;
  

  while ((c = getchar()) != EOF) {
    if (isalpha(c)) {
      if (!inword) {
	inword = 1;
	if (strchr("aeiouAEIOU", c)) {
	  cons = 0;
	  putchar(c);
	} else {
	  cons = c;
	}
      } else {
	putchar(c);
      }
    } else {
      if (inword) {
	inword = 0;
	if (!cons) {
	  printf("ay");
	} else {
	  printf("%cay", cons);
	}
      }
      putchar(c);
    }
  }
  return 0;
}
