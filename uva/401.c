/* @JUDGE_ID: 1102NT 401 C "" */

#include <stdio.h>
#include <string.h>

char *reverse[] = {
  "AA",
  "E3",
  "HH",
  "II",
  "JL",
  "LJ",
  "MM",
  "OO",
  "S2",
  "TT",
  "UU",
  "VV",
  "WW",
  "XX",
  "YY",
  "Z5",
  "11",
  "2S",
  "3E",
  "5Z",
  "88"
};

int rev_size = sizeof(reverse) / sizeof(char *);

void strrev(char *s, char *t)
{
  int n = strlen(s);
  int i;
  
  for (i = 0; i < n; i++) {
    t[i] = s[n-1-i];
  }
  t[n] = 0;
}

char find(char c)
{
  int i;
  for (i = 0; i < rev_size; i++) {
    if (reverse[i][0] == c) {
      return reverse[i][1];
    }
  }
  return 0;
}

void strmirrorrev(char *s, char *t)
{
  int n = strlen(s);
  int i;

  for (i = 0; i < n; i++) {
    t[i] = find(s[n-1-i]);
  }
  t[n] = 0;
}

int main(void)
{
  char s[21], t[21];
  int pal, mirror;
  
  while (scanf("%s", s) == 1) {
    strrev(s, t);
    pal = !strcmp(s, t);
    strmirrorrev(s, t);
    mirror = !strcmp(s, t);
    
    printf("%s -- is ", s);
    if (pal && mirror) {
      printf("a mirrored palindrome.\n");
    } else if (pal && !mirror) {
      printf("a regular palindrome.\n");
    } else if (!pal && mirror) {
      printf("a mirrored string.\n");
    } else {
      printf("not a palindrome.\n");
    }
    printf("\n");
  }
  return 0;
}
