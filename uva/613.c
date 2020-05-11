/* @JUDGE_ID: 1102NT 613 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_STEP 15
#define MAX_DIGIT 80

char history[MAX_STEP+1][MAX_DIGIT+1];

void next(char *str1, char *str2)
{
  int n, i;
  int freq[10];
  char buffer[100];

  for (i = 0; i < 10; i++) {
    freq[i] = 0;
  }

  n = strlen(str1);
  for (i = 0; i < n; i++) {
    assert('0' <= str1[i] && str1[i] <= '9');
    freq[str1[i]-'0']++;
  }
  
  str2[0] = 0;
  for (i = 0; i < 10; i++) {
    if (freq[i] > 0) {
      sprintf(buffer, "%d%d", freq[i], i);
      strcat(str2, buffer);
    }
  }  
}

int find(char *buffer, int n)
{
  int i;

  for (i = 0; i < n; i++) {
    if (!strcmp(buffer, history[i])) {
      return i;
    }
  }
  return -1;
}


int solve_case(void)
{
  int i, j, done;
  char buffer[MAX_DIGIT+1];

  while (scanf("%s", history[0]) == 1 && strcmp(history[0], "-1")) {
    i = 0;
    done = 0;
    while (i < MAX_STEP && !done) {
      next(history[i], buffer);
      j = find(buffer, i+1);
      if (j == i && i == 0) {
	printf("%s is self-inventorying\n", history[0]);
	done = 1;
      } else if (j == i && i > 0) {
	printf("%s is self-inventorying after %d steps\n", history[0],
	       j);
	done = 1;
      } else if (j >= 0) {
	printf("%s enters an inventory loop of length %d\n", history[0],
	       i+1-j);
	done = 1;
      } else {
	strcpy(history[i+1], buffer);
      }
      i++;
    }
    if (!done) {
      printf("%s can not be classified after 15 iterations\n", history[0]);
    }
  }
  return 0;
}

int main(void)
{
  solve_case();
  return 0;
}
