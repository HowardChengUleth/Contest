#include <stdio.h>
#include <string.h>

char words[70][17];
char plain[17];
int num_words;

int possible(int k) 
{
  int i, j;
  int plain_len = strlen(plain);
  int match;

  for (i = 0; i < num_words; i++) {
    if (strlen(words[i]) != plain_len) continue;

    match = 1;
    for (j = 0; words[i][j] && match; j++) {
      if (words[i][j] != 'a' + (plain[j] - 'a' + k) % 26) {
	match = 0;
      }
    }
    if (match) {
      return 1;
    }
  }

  return 0;
}

int main(void)
{
  int cases;
  char buffer[72], *p;
  int k;

  scanf("%d\n", &cases);
  while (cases-- > 0) {
    fgets(buffer, 72, stdin);
    num_words = 0;
    for (p = buffer; p = strtok(p, " \n"); p = NULL) {
      strcpy(words[num_words++], p);
    }
    scanf("%s\n", plain);
    for (k = 0; k < 26; k++) {
      if (possible(k)) {
	printf("%c", 'a'+k);
      }
    }
    printf("\n");
  }
  return 0;
}
