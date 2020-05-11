/* @JUDGE_ID: 1102NT 101 C "Simultation" */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_N 25

int stack[MAX_N][MAX_N];
int height[MAX_N];

void init_stack(void);
int find_stack(int elem, int *index);
void add_stack(int index, int elem);
void move_onto(int a, int b);
void move_over(int a, int b);
void pile_onto(int a, int b);
void pile_over(int a, int b);
void print_stack(void);

int n;

int main(void)
{
  char command1[100], command2[100];
  int a, b;

  scanf("%d", &n);
  init_stack();

  /* get command */
  scanf("%s", command1);
  while (strcmp(command1, "quit")) {
    /* read in the rest of the arguments */
    scanf("%d %s %d", &a, command2, &b);

    if (a != b && find_stack(a, NULL) != find_stack(b, NULL)) {
      if (!strcmp(command1, "move")) {
	if (!strcmp(command2, "onto")) {
	  move_onto(a, b);
	} else if (!strcmp(command2, "over")) {
	  move_over(a, b);
	} else {
	  printf("Big trouble\n");
	  exit(1);
	}
      } else if (!strcmp(command1, "pile")) {
	if (!strcmp(command2, "onto")) {
	  pile_onto(a, b);
	} else if (!strcmp(command2, "over")) {
	  pile_over(a, b);
	} else {
	  printf("Big trouble\n");
	  exit(1);
	}
      } else {
	printf("Big trouble!\n");
	exit(1);
      }
    }
    scanf("%s", command1);
  }

  print_stack();
  return 0;
}

void init_stack(void)
{
  int i;

  for (i = 0; i < n; i++) {
    stack[i][0] = i;
    height[i] = 1;
  }
}

int find_stack(int elem, int *index)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < height[i]; j++) {
      if (stack[i][j] == elem) {
	if (index) {
	  *index = j;
	}
	return i;
      }
    }
  }

  printf("Help, cannot find in stack\n");
  printf("elem = %d\n", elem);
  printf("stack = \n");
  print_stack();
  exit(1);
}

void print_stack(void)
{
  int i, j;

  for (i = 0; i < n; i++) {
    printf("%d:", i);
    for (j = 0; j < height[i]; j++) {
      printf(" %d", stack[i][j]);
    }
    printf("\n");
  }
}

void add_stack(int index, int elem)
{
  stack[index][height[index]] = elem;
  height[index]++;
}

void return_stack(int stack_no, int index)
{
  /* return all the elements above index to their initial positions */
  int i, elem;
  int flag = 0;

  for (i = index+1; i < height[stack_no]; i++) {
    elem = stack[stack_no][i];
    if (stack_no != elem) {
      add_stack(elem, elem);
    } else {
      flag = 1;
    }
  }
  height[stack_no] = index+1;
  if (flag) {
    add_stack(stack_no, stack_no);
  }
}

void move_onto(int a, int b)
{
  int s_a, s_b, i_a, i_b;

  s_a = find_stack(a, &i_a);
  s_b = find_stack(b, &i_b);
  return_stack(s_a, i_a);
  return_stack(s_b, i_b);
  add_stack(s_b, a);
  height[s_a]--;
}

void move_over(int a, int b)
{
  int s_a, s_b, i_a;
  s_a = find_stack(a, &i_a);
  s_b = find_stack(b, NULL);
  return_stack(s_a, i_a);
  add_stack(s_b, a);
  height[s_a]--;
}

void pile_onto(int a, int b)
{
  int s_a, s_b, i_a, i_b;
  int i;

  s_a = find_stack(a, &i_a);
  s_b = find_stack(b, &i_b);
  return_stack(s_b, i_b);
  for (i = i_a; i < height[s_a]; i++) {
    add_stack(s_b, stack[s_a][i]);
  }
  height[s_a] = i_a;
}

void pile_over(int a, int b)
{
  int s_a, s_b, i_a;
  int i;

  s_a = find_stack(a, &i_a);
  s_b = find_stack(b, NULL);
  for (i = i_a; i < height[s_a]; i++) {
    add_stack(s_b, stack[s_a][i]);
  }
  height[s_a] = i_a;
}
