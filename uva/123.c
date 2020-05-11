/* @JUDGE_ID: 1102NT 123 C "" */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_IGNORE      50
#define MAX_IGNORE_LEN  11
#define MAX_TITLE       200
#define MAX_TITLE_WORDS 15
#define MAX_ENTRY       MAX_TITLE * MAX_TITLE_WORDS

typedef struct {
  char title[2501];
  char keyword[2501];
  int pos;
} Entry;

char ignore[MAX_IGNORE][MAX_IGNORE_LEN];
Entry entry[MAX_ENTRY];
int num_ignore;
int num_entry;

int cmp(const void *a, const void *b)
{
  Entry *x = (Entry *)a;
  Entry *y = (Entry *)b;

  int t = strcmp(x->keyword, y->keyword);
  if (t) {
    return t;
  } else {
    return x->pos - y->pos;
  }

}

int to_ignore(char *keyword)
{
  int i;

  for (i = 0; i < num_ignore; i++) {
    if (!strcmp(ignore[i], keyword)) {
      return 1;
    }
  }
  return 0;
}

int main(void)
{
  char buffer[10001];
  char buffer2[10001];
  char *ptr;
  char *ptr1, *ptr2;
  int i;
  int c;
  int new_pos;

  num_ignore = num_entry = 0;
  while (scanf("%s", buffer) == 1 && strcmp(buffer, "::")) {
    for (i = 0; i < strlen(buffer); i++) {
      ignore[num_ignore][i] = toupper(buffer[i]);
    }
    ignore[num_ignore][i] = '\0';
    num_ignore++;
  }
  c = getchar();
  assert(c == '\n');
  new_pos = 0;
  while (fgets(buffer, 10001, stdin)) {
    strcpy(buffer2, buffer);
    ptr = strtok(buffer2, " \n");
    ptr1 = buffer2;
    while (ptr) {
      ptr2 = strstr(ptr1, ptr);
      entry[num_entry].pos = new_pos++;
      c = ptr2 - buffer2;
      for (i = 0; i < strlen(buffer); i++) {
        if (i < c || i >= c + strlen(ptr)) {
          entry[num_entry].title[i] = tolower(buffer[i]);
        } else {
          entry[num_entry].title[i] = toupper(buffer[i]);
        }
      }
      entry[num_entry].title[strlen(buffer)] = '\0';
      strcpy(entry[num_entry].keyword, ptr);
      for (i = 0; i < strlen(entry[num_entry].keyword); i++) {
        entry[num_entry].keyword[i] = toupper(entry[num_entry].keyword[i]);
      }
      if (!to_ignore(entry[num_entry].keyword)) {
        num_entry++;
      }
      ptr1 = ptr2 + strlen(ptr) + 1;
      ptr = strtok(NULL, " \n");
    }
  }


  qsort(entry, num_entry, sizeof(Entry), cmp);
  for (i = 0; i < num_entry; i++) {
    printf("%s", entry[i].title);
  }

  return 0;
}
