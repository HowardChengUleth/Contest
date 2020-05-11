#include <stdio.h>
#include <ctype.h>
#include <string.h>

int end_char(int c)
{
  return isspace(c) || c == '?' || c == '!' || c == ',' || c == '.';
}

int main(void)
{
  char line[200];
  int count[31];
  int i, j, k, len, n;
  int last, empty;

  while (fgets(line, 200, stdin) && line[0] != '#') {
    for (i = 0; i <= 30; i++) {
      count[i] = 0;
    }
    last = 0;
    empty = 1;
    do {
      n = strlen(line);
      line[--n] = 0;
      for (i = 0; i < n; i=j) {
	len = 0;
	while (i < n && end_char(line[i])) {
	  i++;
	}
	for (j = i; j < n && !end_char(line[j]); j++)
	  ;
	for (k = i; k < j && k < n; k++) {
	  if (!end_char(line[k]) && line[k] != '\'' && line[k] != '-') {
	    len++;
	  }
	}
	
	if (len) {
	  empty = 0;
	}
	if (j >= n && line[n-1] == '-') {
	  last = len;
	} else {
	  count[last+len]++;
	  last = 0;
	}
      }
    
    } while (fgets(line, 200, stdin) && line[0] != '#');

    if (last) {
      count[last]++;
    }
    if (empty) {
      continue;
    }
    for (i = 1; i <= 30; i++) {
      if (count[i]) {
	printf("%d %d\n", i, count[i]);
      }
    }
    printf("\n");
  }

  return 0;
}
