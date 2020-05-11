#include <stdio.h>
#include <string.h>

typedef struct {
  char *word;
  int val;
} Data;

Data values[] = {
  { "zero", 0 }, { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 },
  { "five", 5 }, { "six", 6 }, { "seven", 7 }, { "eight", 8 }, { "nine", 9 },
  { "ten", 10 }, { "eleven", 11 }, { "twelve", 12 }, { "thirteen", 13 },
  { "fourteen", 14 }, { "fifteen", 15 }, { "sixteen", 16 }, 
  { "seventeen", 17 }, { "eighteen", 18 }, { "nineteen", 19 }, 
  { "twenty", 20 }, { "thirty", 30 }, { "forty", 40 }, { "fifty", 50 },
  { "sixty", 60 }, { "seventy", 70 }, { "eighty", 80 }, { "ninety", 90 },
  { "hundred", 100 }, { "thousand", 1000 }, { "million", 1000000 } };

int n = sizeof(values) / sizeof(Data);

int translate(char *line)
{
  char *p;
  int sum;
  int i;

  if (!strncmp("negative", line, strlen("negative"))) {
    return -translate(line + strlen("negative "));
  }

  /* look for million */
  if (p = strstr(line, " million")) {
    *p = 0;
    if (*(p+strlen(" million"))) {
      return translate(line) * 1000000 + translate(p+strlen(" million"));
    } else {
      return translate(line) * 1000000;
    }
  }

  /* look for thousand */
  if (p = strstr(line, " thousand")) {
    *p = 0;
    if (*(p+strlen(" thousand"))) {
      return translate(line) * 1000 + translate(p+strlen(" thousand"));
    } else {
      return translate(line) * 1000;
    }
  }

  /* look for hundred */
  if (p = strstr(line, " hundred")) {
    *p = 0;
    if (*(p+strlen(" hundred"))) {
      return translate(line) * 100 + translate(p+strlen(" hundred"));
    } else {
      return translate(line) * 100;
    }
  }

  sum = 0;
  for (p = line; p = strtok(p, " \n"); p = NULL) {
    for (i = 0; i < n; i++) {
      if (!strcmp(values[i].word, p)) {
	sum += values[i].val;
	break;
      }
    }
  }
  return sum;
}

int main(void)
{
  char line[10000];

  while (fgets(line, 10000, stdin)) {
    printf("%d\n", translate(line));
  }
  return 0;
}
