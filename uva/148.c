#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 2000
#define MAX_LEN 20

char dict[MAX_WORDS+1][MAX_LEN+1];
int len[MAX_WORDS];
int dict_freq[MAX_WORDS][26];
int num_dict;

void read_dict(void)
{
  int i;
  while (scanf("%s\n", dict[num_dict]) == 1 && strcmp(dict[num_dict], "#")) {
    len[num_dict] = strlen(dict[num_dict]);
    for (i = 0; i < len[num_dict]; i++) {
      dict_freq[num_dict][dict[num_dict][i]-'A']++;
    }
    num_dict++;
  }
}

int same(char word_list[MAX_WORDS][MAX_LEN+1], int num_words, 
	 int *used, int num_used)
{
  int i;
  if (num_words != num_used) {
    return 0;
  }
  for (i = 0; i < num_words; i++) {
    if (strcmp(word_list[i], dict[used[i]])) {
      return 0;
    }
  }
  return 1;
}

void solve(char *line, int *freq, int count, int index, 
	   char word_list[MAX_WORDS][MAX_LEN+1], int num_words,
	   int *used, int num_used)
{
  char fit;
  int i;

  if (!count) {
    if (!same(word_list, num_words, used, num_used)) {
      printf("%s =", line);
      for (i = 0; i < num_used; i++) {
	printf(" %s", dict[used[i]]);
      }
      printf("\n");
    }
    return;
  }
  if (index >= num_dict) {
    return;
  }

  fit = len[index] <= count;
  for (i = 0; fit && i < 26; i++) {
    if (dict_freq[index][i] > freq[i]) fit = 0;
  }
  if (fit) {
    for (i = 0; i < 26; i++) {
      freq[i] -= dict_freq[index][i];
    }
    used[num_used] = index;
    solve(line, freq, count-len[index], index+1, word_list, num_words,
	  used, num_used+1);
    for (i = 0; i < 26; i++) {
      freq[i] += dict_freq[index][i];
    }
  }

  solve(line, freq, count, index+1, word_list, num_words, used, num_used);
}

int main(void)
{
  char line[1024];
  char line2[1024];
  char *p;
  int used[MAX_WORDS];
  int freq[26];
  int i;
  int count;
  char word_list[MAX_WORDS][MAX_LEN+1];
  int num_words;

  read_dict();
  while (fgets(line, 1024, stdin) && strcmp(line, "#\n")) {
    line[strlen(line)-1] = 0;
    count = 0;
    for (i = 0; i < 26; i++) {
      freq[i] = 0;
    }
    memset(used, 0, num_dict);
    for (i = 0; i < strlen(line); i++) {
      if (isalpha(line[i])) {
	freq[line[i]-'A']++;
	count++;
      }
    }
    strcpy(line2, line);
    num_words = 0;
    for (p = line2; p = strtok(p, " "); p = NULL) {
      strcpy(word_list[num_words++], p);
    }
    qsort(word_list, num_words, MAX_LEN+1, strcmp);

    solve(line, freq, count, 0, word_list, num_words, used, 0);
  }


  return 0;
}
