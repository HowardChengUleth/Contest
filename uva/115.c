/* @JUDGE_ID: 1102NT 115 C "" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN   33
#define MAX_NAMES 300

typedef struct {
  char name[MAX_LEN];
  int parent;
} Person;

Person tree[MAX_NAMES];
int n;

int find(char *name);
void insert(char *child, char *parent);
int query_child(char *name1, char *name2);
int query_cousin(char *name1, char *name2, int *times, int *removed);
void query(char *name1, char *name2);

int main(void) {
  char name1[MAX_LEN], name2[MAX_LEN];
  int i;

  for (i = 0; i < MAX_NAMES; i++) {
    tree[i].name[0] = 0;
    tree[i].parent = -1;
  }

  n = 0;
  scanf("%s %s", name1, name2);
  while (strcmp(name1, "no.child")) {
    insert(name1, name2);
    scanf("%s %s", name1, name2);
  }
  while (scanf("%s %s", name1, name2) == 2) {
    query(name1, name2);
  }

  return 0;
}

/* returns index, or -1 if not found */
int find(char *name)
{
  int i;
  for (i = 0; i < n; i++) {
    if (!strcmp(name, tree[i].name)) {
      return i;
    }
  }
  return -1;
}

void insert(char *child, char *parent)
{
  int i1, i2;

  i1 = find(child);
  i2 = find(parent);

  if (i1 >= 0) {
    if (i2 >= 0) {
      /* both in there, just set a link */
      assert(tree[i1].parent == -1 || tree[i1].parent == i2);
      tree[i1].parent = i2;
    } else {
      /* insert parent */
      strcpy(tree[n].name, parent);
      tree[n].parent = -1;
      assert(tree[i1].parent == -1 || tree[i1].parent == n);
      tree[i1].parent = n;
      n++;
    }
  } else {
    if (i2 >= 0) {
      /* insert child */
      strcpy(tree[n].name, child);
      tree[n].parent = i2;
      n++;
    } else {
      /* insert both */
      strcpy(tree[n].name, child);
      tree[n].parent = n+1;
      n++;
      strcpy(tree[n].name, parent);
      tree[n].parent = -1;
      n++;
    }
  }
}

int query_ancestor(char *name1, char *name2)
{
  int r;
  int count = 0;
  int p = find(name1);
  int q = find(name2);

  r = tree[q].parent;
  count = 0;
  while (r != -1 && r != p) {
    count++;
    r = tree[r].parent;
  }
  if (r == p) {
    return count;
  } else {
    /*
    assert(r == -1); */
    return -1;
  }
}

int query_cousin(char *name1, char *name2, int *times, int *removed)
{
  int r;
  int m, n;
  int found;

  r = find(name1);
  found = 0;
  while (r != -1 && !found) {
    r = tree[r].parent;
    n = query_ancestor(tree[r].name, name2);
    if (n >= 0) {
      m = query_ancestor(tree[r].name, name1);
      found = 1;
      *times = (n < m) ? n : m;
      *removed = n - m;
      if (*removed < 0) {
	*removed *= -1;
      }
    }
  } 
  
  return found;
}

void query(char *name1, char *name2)
{
  int t;
  int i;
  int times, removed;

  if (find(name1) >= 0 && find(name2) >= 0) {
    t = query_ancestor(name1, name2);
    if (t >= 0) {
      for (i = 0; i < t-1; i++) {
	printf("great ");
      }
      if (t > 0) {
	printf("grand ");
      }
      printf("parent\n");
      return;
    }
    
    t = query_ancestor(name2, name1);
    if (t >= 0) {
      for (i = 0; i < t-1; i++) {
	printf("great ");
      }
      if (t > 0) {
	printf("grand ");
      }
      printf("child\n");
      return;
    }
    
    if (query_cousin(name1, name2, &times, &removed)) {
      if (times == 0 && removed == 0) {
	printf("sibling\n");
      } else if (times > 0 && removed == 0) {
	printf("%d cousin\n", times);
      } else {
	printf("%d cousin removed %d\n", times, removed);
      }
      return;
    }
  }
  
  printf("no relation\n");
}
