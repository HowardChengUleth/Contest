/* @JUDGE_ID: 1102NT 843 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int n;
char dict[1000][18];

int possible(const char *plain, const char *cipher, 
	     const char *map, const char *used, 
	     char *newmap, char *newused)
{
  int i;

  memset(newmap, '*', 26);
  memset(newused, 0, 26);

  for (i = 0; plain[i]; i++) {
    if (map[cipher[i]-'a'] == '*') {
      if (newmap[cipher[i]-'a'] == '*') {
	newmap[cipher[i]-'a'] = plain[i];
      } else if (newmap[cipher[i]-'a'] != plain[i]) {
	return 0;
      }
    } else if (map[cipher[i]-'a'] != plain[i]) {
      return 0;
    }
  }
  for (i = 0; i < 26; i++) {
    if (newmap[i] != '*' && map[i] != '*' && newmap[i] != map[i]) {
      return 0;
    }
    if (map[i] == '*' && newmap[i] != '*' && used[newmap[i]-'a']) {
      return 0;
    }
    if (newmap[i] == '*') {
      newmap[i] = map[i];
    }
    if (newmap[i] != '*') {
      newused[newmap[i]-'a'] = 1;
    }
  }
  return 1;
}

int search(char *line, int index, char *map, char *used)
{
  char word[1024];
  char newmap[26], newused[26];
  int i, l, t;

  assert(line);
  assert(map);
  assert(used);
  if (line[index] == 0) {
    /* all done! */
    return 1;
  }

  if (isspace(line[index])) {
    /* just skip the space */
    return search(line, index+1, map, used);
  }

  /*
  for (i = 0; i < index; i++) {
    printf("-");
  }
  printf(">");
  for (i = 0; i < strlen(line); i++) {
    if (isspace(line[i])) putchar(line[i]);
    else putchar(map[line[i]-'a']);
  }
  */

  /* look for the next word */
  for (l = 0; !isspace(line[index+l]); l++) {
    word[l] = line[index+l];
  }
  word[l] = 0;

  for (i = 0; i < n; i++) {
    if (strlen(dict[i]) < l) continue;
    if (strlen(dict[i]) > l) break;
    t = possible(dict[i], word, map, used, newmap, newused);
    if (t && search(line, index+l, newmap, newused)) {
      memcpy(map, newmap, 26);
      return 1;
    }
  }

  return 0;
}

int mycmp(const void *a, const void *b)
{
  const char *x = (const char *)a, *y = (const char *)b;

  return strlen(x)-strlen(y);
}

int main(void)
{
  char line[1024];
  char map[26], used[26];
  int i;

  scanf("%d\n", &n);
  for (i = 0; i < n; i++) {
    fgets(dict[i], 18, stdin);
    dict[i][strlen(dict[i])-1] = 0;   /* clears the '\n' */
  }
  qsort(dict, n, 18, mycmp);

  while (fgets(line, 1024, stdin)) {
    memset(map, '*', 26);
    memset(used, 0, 26);
    if (!search(line, 0, map, used)) {
      memset(map, '*', 26);
    }
    for (i = 0; i < strlen(line); i++) {
      if (isspace(line[i])) {
	putchar(line[i]);
      } else {
	putchar(map[line[i]-'a']);
      }
    }
  }

  return 0;
}

