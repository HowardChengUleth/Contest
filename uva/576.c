/* @JUDGE_ID: 1102NT 576 C "" */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char vowels[7] = "aeiouy";
char end[3] = "/\n";
int syl_count[3] = {5, 7, 5};

void check_line(char *line)
{
  int i;
  int state, syl, num;

  state = syl = num = 0;
  i = 0;
  
  while (1) {
    if (strchr(vowels, line[i])) {
      state = 1;
    } else if (strchr(end, line[i])) {
      if (state == 1) {
	syl++;
      }
      if (syl != syl_count[num]) {
	printf("%d\n", num+1);
	return;
      } else {
	if (num == 2) {
	  printf("Y\n");
	  return;
	} else {
	  num++;
	  syl = 0;
	  state = 0;
	}
      }
    } else {
      assert(isalpha(line[i]) || line[i] == ' ');
      if (state == 1) {
	syl++;
      }
      state = 0;
    }
    i++;
  }
}

int main(void)
{
  char line[300];

  while (fgets(line, 300, stdin) && strcmp(line, "e/o/i\n")) {
    check_line(line);
  }
  return 0;
}
