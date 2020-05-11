/* @JUDGE_ID: 1102NT 110 C " " */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *varname = " abcdef";
int n;

void swap(int *order, int a, int b)
{
  int t = order[a];
  order[a] = order[b];
  order[b] = t;
}

void shift_down(int *order, int src, int dest)
{
  int i, t;

  assert(src > dest);
  t = order[src];
  for (i = src; i > dest; i--) {
    order[i] = order[i-1];
  }
  order[dest] = t;
}

void shift_up(int *order, int src, int dest)
{
  int i, t;

  assert(src < dest);
  t = order[src];
  for (i = src; i < dest; i++) {
    order[i] = order[i+1];
  }
  order[dest] = t;
}

void print_vars(int n)
{
  int i;
  for (i = 1; i <= n-1; i++) {
    printf("%c,", varname[i]);
  }
  printf("%c", varname[n]);
}

void print_indent(int indent)
{
  int i;
  for (i = 0; i < indent; i++) {
    printf(" ");
  }
}

void print_order(int *order)
{
  int i;
  printf("writeln(");
  for (i = 1; i <= n-1; i++) {
    printf("%c,", varname[order[i]]);
  }
  printf("%c)\n", varname[order[n]]);
}

void print_cmp(int *order, int a, int b)
{
  printf("if %c < %c then\n", varname[order[a]], varname[order[b]]);
}

void print_sort(int *order, int index, int indent)
{
  int i;

  if (index == n) {
    print_indent(indent);
    print_order(order);
    return;
  }

  /* we have some work to do */

  /* the if part */
  print_indent(indent);
  print_cmp(order, index, index+1);
  print_sort(order, index+1, indent+2);

  /* the else if part */
  for (i = index-1; i >= 0; i--) {
    print_indent(indent);
    if (i == 0) {
      printf("else\n");
    } else {
      printf("else ");
      print_cmp(order, i, index+1);
    }
    shift_down(order, index+1, i+1);
    print_sort(order, index+1, indent+2);
    shift_up(order, i+1, index+1);
  }
}

int main(void)
{
  int order[7] = {0, 1, 2, 3, 4, 5, 6};
  
  scanf("%d", &n);
  assert(1 <= n && n <= 6);
  printf("program sort(input,output);\n");
  printf("var\n");
  print_vars(n);
  printf(" : integer;\n");
  printf("begin\n");
  printf("  readln("); print_vars(n); printf(");\n");
  print_sort(order, 1, 2);
  printf("end.\n");
  return 0;
}
