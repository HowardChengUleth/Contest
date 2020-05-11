#include <stdio.h>
#include <string.h>

char *code[7] = {
  "",
  "BFPV",
  "CGJKQSXZ",
  "DT",
  "L",
  "MN",
  "R"
};

int soundex(char c)
{
  int i;
  
  for (i = 1; i <= 6; i++) {
    if (strchr(code[i], c)) {
      return i;
    }
  }
  return 0;
}

int main(void)
{
  char word[21];
  int i, curr, last;

  while (scanf("%s", word) == 1) {
    last = 0;
    for (i = 0; word[i]; i++) {
      curr = soundex(word[i]);
      if (curr != last && curr) {
	printf("%d", curr);
      }
      last = curr;
    }
    printf("\n");
  }
  return 0;
}
