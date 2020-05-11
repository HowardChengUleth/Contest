/* @JUDGE_ID: 1102NT 10415 C "" */

#include <stdio.h>
#include <string.h>

char *finger[14] = {
  "0111001111",
  "0111001110",
  "0111001100",
  "0111001000",
  "0111000000",
  "0110000000",
  "0100000000",
  "0010000000",
  "1111001110",
  "1111001100",
  "1111001000",
  "1111000000",
  "1110000000",
  "1100000000"
};

char *notemap = "cdefgabCDEFGAB";

void fingers(char note, char *set)
{
  int i;

  i = strchr(notemap, note) - notemap;
  strcpy(set, finger[i]);
}

int main(void)
{
  int t;
  char buffer[202];
  int i, j;
  char set[11], newset[11];
  int count[10];

  scanf("%d\n", &t);
  while (t-- > 0) {
    fgets(buffer, 202, stdin);
    strcpy(set, "0000000000");
    for (i = 0; i < 10; i++) {
      count[i] = 0;
    }

    for (i = 0; buffer[i] != '\n'; i++) {
      fingers(buffer[i], newset);
      for (j = 0; j < 10; j++) {
	if (newset[j] == '1' && set[j] == '0') {
	  count[j]++;
	}
      }
      strcpy(set, newset);
    }

    for (i = 0; i < 10; i++) {
      printf("%d%c", count[i], (i == 9) ? '\n' : ' ');
    }
  }

  return 0;
}
