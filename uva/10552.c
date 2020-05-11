/* @JUDGE_ID: 1102NT 10552 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
  char name[101], birth[101], death[101];
  int mother, father, children[200];
  int num_children;
} Person;

Person person[200];
int n;

void new_person(char *name, int i)
{
  strcpy(person[i].name, name);
  person[i].birth[0] = person[i].death[0] = 0;
  person[i].mother = person[i].father = -1;
  person[i].num_children = 0;
}

int find_person(char *name)
{
  int i;

  for (i = 0; i < n; i++) {
    if (!strcmp(name, person[i].name)) {
      return i;
    }
  }
  new_person(name, n++);
  return n-1;
}

void print_person(int p, int indent)
{
  int i;

  for (i = 0; i < indent; i++) {
    putchar(' ');
  }
  printf("%s", person[p].name);
  if (person[p].birth[0]) {
    printf(" %s -", person[p].birth);
    if (person[p].death[0]) {
      printf(" %s", person[p].death);
    }
  }
  printf("\n");
}

void trim(char *s)
{
  int i;

  for (i = strlen(s)-1; s[i] == ' '; i--) {
    s[i] = 0;
  }
}

void process_birth(void)
{
  char *p, temp[101];
  int i, j;

  p = strtok(0, ":");
  strcpy(temp, p);
  trim(temp);
  i = find_person(temp);
  
  p = strtok(0, ":");
  while (*p == ' ') p++;
  strcpy(temp, p);
  trim(temp);
  strcpy(person[i].birth, temp);

  p = strtok(0, ":");
  while (*p == ' ') p++;
  strcpy(temp, p);
  trim(temp);
  j = find_person(temp);
  person[i].mother = j;
  person[j].children[person[j].num_children++] = i;

  p = strtok(0, "\n");
  while (*p == ' ') p++;
  strcpy(temp, p);
  trim(temp);
  j = find_person(temp);
  person[i].father = j;
  person[j].children[person[j].num_children++] = i;
}

void process_death(void)
{
  char *p, temp[101];
  int i;

  p = strtok(0, ":");
  strcpy(temp, p);
  trim(temp);
  i = find_person(temp);
  
  p = strtok(0, "\n");
  while (*p == ' ') p++;
  strcpy(temp, p);
  trim(temp);
  strcpy(person[i].death, temp);
}

void print_ancestor(int p, int indent)
{
  int m, f;

  print_person(p, indent);
  m = person[p].mother;
  f = person[p].father;
  if (m == -1 && f == -1) {
    return;
  }
  assert(m >= 0 && f >= 0);
  if (strcmp(person[m].name, person[f].name) < 0) {
    print_ancestor(m, indent+2);
    print_ancestor(f, indent+2);
  } else {
    print_ancestor(f, indent+2);
    print_ancestor(m, indent+2);
  }
}

void process_ancestor(void)
{
  char *p, temp[101];
  int m, f, i;

  p = strtok(0, "\n");
  strcpy(temp, p);
  trim(temp);
  i = find_person(temp);
  printf("ANCESTORS of %s\n", temp);
  
  m = person[i].mother;
  f = person[i].father;
  assert(m >= 0 && f >= 0);
  if (strcmp(person[m].name, person[f].name) < 0) {
    print_ancestor(m, 2);
    print_ancestor(f, 2);
  } else {
    print_ancestor(f, 2);
    print_ancestor(m, 2);
  }
}

int cmp(const void *a, const void *b)
{
  int c1 = *(int *)a, c2 = *(int *)b;

  return strcmp(person[c1].name, person[c2].name);
}

void print_descendant(int p, int indent)
{
  int j;

  print_person(p, indent);
  qsort(person[p].children, person[p].num_children, sizeof(int), cmp);
  for (j = 0; j < person[p].num_children; j++) {
    print_descendant(person[p].children[j], indent+2);
  }
}

void process_descendants(void)
{
  char *p, temp[101];
  int i, j;

  p = strtok(0, "\n");
  strcpy(temp, p);
  trim(temp);
  i = find_person(temp);
  printf("DESCENDANTS of %s\n", temp);
  
  qsort(person[i].children, person[i].num_children, sizeof(int), cmp);
  for (j = 0; j < person[i].num_children; j++) {
    print_descendant(person[i].children[j], 2);
  }
}

int main(void)
{
  char line[101], *p;
  int first = 1;

  while (fgets(line, 101, stdin)) {
    p = strtok(line, " ");
    if (!strcmp(p, "BIRTH")) {
      process_birth();
    } else if (!strcmp(p, "DEATH")) {
      process_death();
    } else if (!strcmp(p, "ANCESTORS")) {
      if (!first) {
	printf("\n");
      }
      process_ancestor();
      first = 0;
    } else if (!strcmp(p, "DESCENDANTS")) {
      if (!first) {
	printf("\n");
      }
      process_descendants();
      first = 0;
    } else if (!strcmp(p, "QUIT\n")) {
      break;
    } else {
      printf("Bad input! '%s'\n", p);
      return -1;
    }
  }
  return 0;
}
  
