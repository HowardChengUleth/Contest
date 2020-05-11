#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char var[21];
char relat[20][20];
int num;

int cmp(const void *a, const void *b)
{
  char *x = (char *)a;
  char *y = (char *)b;
  return *x - *y;
}

int var_index(char c)
{
  char *ptr = strchr(var, c);
  assert(ptr);
  return ptr-var;
}

int con_sat(char *str, int index)
{
  int i, j1, j2;
  
  j2 = var_index(str[index]);
  for (i = index+1; i < num; i++) {
    j1 = var_index(str[i]);
    if (relat[j1][j2]) {
      return 0;
    }
  }
  return 1;
}

void print_perm(char *str, int index)
{
  char old_str[21];
  char t;
  int i;

  if (index == num) {
    printf("%s\n", str);
    return;
  }

  for (i = index; i < num; i++) {
    strcpy(old_str, str);
    t = str[index];
    str[index] = str[i];
    str[i] = t;
    if (con_sat(str, index)) {
      qsort(str+index+1, num-index-1, 1, cmp);
      print_perm(str, index+1);
    }
    strcpy(str, old_str);
  }
}


int main(void)
{
  char buffer[10240];
  char str[10240];
  int i, j;
  int index1, index2;
  int count = 0;

  while (fgets(buffer, 10240, stdin)) {
    /* read in variable names */
    num = 0;
    for (i = 0; i < strlen(buffer); i++) {
      if (isalpha(buffer[i])) {
	var[num++] = buffer[i];
      }
    }
    var[num] = 0;
    if (num) {
      if (++count > 1) {
	printf("\n");
      }
      qsort(var, num, 1, cmp);
      
      for (i = 0; i < num; i++) {
	for (j = 0; j < num; j++) {
	  relat[i][j] = 0;
	}
      }
      
      /* read in constraints */
      fgets(buffer, 10240, stdin);
      for (i = 0; i < strlen(buffer); i++) {
	if (isalpha(buffer[i])) {
	  index1 = var_index(buffer[i]);
	  i++;
	  while (!isalpha(buffer[i]) && i < strlen(buffer)) {
	    i++;
	  }
	  index2 = var_index(buffer[i]);
	  relat[index1][index2] = 1;
	}
      }
    
      /* do permutation */
      strcpy(str, var);
      print_perm(str, 0);
    }
  }
  return 0;
}
