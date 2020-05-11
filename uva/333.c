/* @JUDGE_ID: 1102NT 333 C "" */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valid(char *isbn)
{
  int num_digits = 0;
  int s1, s2;
  int i, val;

  s1 = s2 = 0;

  for (i = 0; isbn[i]; i++) {
    if (isbn[i] == '-') continue;
    if (isbn[i] == 'X' && num_digits == 9) {
      val = 10;
    } else if (isdigit(isbn[i])) {
      val = isbn[i] - '0';
    } else {
      return 0;
    }
    s1 += val;
    s2 += s1;
    num_digits++;
  }
  if (num_digits != 10) {
    return 0;
  }
  return (s2 % 11 == 0);
}

int main(void)
{
  char buffer[1000];
  char isbn[1000];
  int i;

  while (fgets(buffer, 1000, stdin)) {
    for (i = 0; isspace(buffer[i]); i++) ;
    strcpy(isbn, buffer+i);
    for (i = strlen(isbn)-1; i >= 0 && isspace(isbn[i]); i--) {
      isbn[i] = 0;
    }

    printf("%s is %s.\n", isbn, valid(isbn) ? "correct" : "incorrect");
  }
  return 0;
}
