#include <stdio.h>
#include <string.h>

void rotate1(char *s)
{
  char t = s[0];
  s[0] = s[4];
  s[4] = s[5];
  s[5] = s[1];
  s[1] = t;
}

void rotate2(char *s)
{
  char t = s[1];
  s[1] = s[3];
  s[3] = s[4];
  s[4] = s[2];
  s[2] = t;
}

void rotate3(char *s)
{
  char t = s[0];
  s[0] = s[3];
  s[3] = s[5];
  s[5] = s[2];
  s[2] = t;
}

int match(char *str1, char *str2)
{
  char str[13];
  int i, j, k, ii;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 4; k++) {
	strcpy(str, str1);
	for (ii = 0; ii < i; ii++) {
	  rotate1(str);
	}
	for (ii = 0; ii < j; ii++) {
	  rotate2(str);
	}
	for (ii = 0; ii < k; ii++) {
	  rotate3(str);
	}
	if (!strcmp(str, str2)) {
	  return 1;
	}
      }
    }
  }
  return 0;
}

int main(void)
{
  char str1[13], str2[13];

  while (scanf("%s", str1) == 1) {
    strcpy(str2, str1+6);
    str1[6] = 0;
    printf("%s\n", (match(str1, str2) ? "TRUE" : "FALSE"));
  }
  return 0;
}
