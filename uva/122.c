#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODE 300

typedef struct dummy {
  int val;          /* -1 if uninitialized, -2 if overinitialized */
  struct dummy *left;
  struct dummy *right;
} Node;

void add_node(Node **node, int val, char *dir)
{
  if (!(*node)) {
    *node = (Node *)malloc(sizeof(Node));
    if (!(*node)) {
      fprintf(stderr, "Out of memory\n");
      exit(1);
    }
    (*node)->val = -1;
    (*node)->left = (*node)->right = 0;
  }

  if (*dir == 0) {
    if ((*node)->val == -1) {
      (*node)->val = val;
    } else {
      (*node)->val = -2;
    }
  } else if (*dir == 'L') {
    add_node(&((*node)->left), val, dir+1);
  } else if (*dir == 'R') {
    add_node(&((*node)->right), val, dir+1);
  }     
}

Node *read_tree(void)
{
  char buffer[10240];
  char dir[10240];
  int done = 0;
  int val;
  char *ptr;
  Node *root = 0;

  if (scanf("%s", buffer) != 1) {
    return 0;
  }

  while (!done) {
    if (!(ptr = strchr(buffer, ','))) {
      done = 1;
    } else {
      *ptr = 0;
      assert(buffer[0] == '(');
      val = atoi(buffer+1);
      ptr++;
      assert(ptr[strlen(ptr)-1] == ')');
      strncpy(dir, ptr, strlen(ptr)-1);
      dir[strlen(ptr)-1] = 0;
      add_node(&root, val, dir);
      scanf("%s", buffer);
    }
  } 
  return root;
}

void print_tree(Node *root)
{
  Node *buff1[MAX_NODE];
  Node *buff2[MAX_NODE];
  char buffer[10240];
  char fmt[1024];
  int num1, num2;
  int val, i;

  if (!root) {
    return;
  }

  num1 = 1;
  buff1[0] = root;
  buffer[0] = 0;

  while (num1 > 0) {
    num2 = 0;
    for (i = 0; i < num1; i++) {
      val = buff1[i]->val;
      if (val < 0) {
	printf("not complete\n");
	return;
      }
      sprintf(fmt, " %d", val);
      strcat(buffer, fmt);
      if (buff1[i]->left) {
	buff2[num2++] = buff1[i]->left;
      }
      if (buff1[i]->right) {
	buff2[num2++] = buff1[i]->right;
      }
    }
    num1 = num2;
    for (i = 0; i < num2; i++) {
      buff1[i] = buff2[i];
    }
  }
  printf("%s\n", buffer+1);

}

void del_tree(Node **root)
{
  if (*root) {
    del_tree(&((*root)->left));
    del_tree(&((*root)->right));
    free(*root);
    *root = 0;
  }
}

int main(void)
{
  Node *root = 0;

  while ((root = read_tree())) {
    print_tree(root);
    del_tree(&root);
  }

  return 0;
}
