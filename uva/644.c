/* @JUDGE_ID: 1102NT 644 C "" */

#include <string.h>
#include <stdio.h>

int main(void)
{
  int set = 1;
  int num, ans, i, j;
  char code[10][100];

  num = 0;
  while (scanf("%s", code[num++]) == 1) {
    while (scanf("%s", code[num]) == 1 && code[num][0] != '9') {
      num++;
    }
    ans = 1;
    for (i = 0; i < num; i++) {
      for (j = 0; j < num; j++) {
	if (i != j && strstr(code[i], code[j]) == &(code[i][0])) {
	  ans = 0;
	}
      }
    }
    if (ans) {
      printf("Set %d is immediately decodable\n", set++);
    } else {
      printf("Set %d is not immediately decodable\n", set++);
    }
    num = 0;
  }
  return 0;
}
