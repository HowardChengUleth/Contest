#include <stdio.h>
#include <string.h>

int degree(char *num)
{
  int sum = 0;
  int i;

  for (i = 0; num[i]; i++) {
    sum += num[i] - '0';
  }
  
  if (sum == 9) {
    return 1;
  }

  i = 0;
  while (sum) {
    /* technically the number is reversed here but it doesn't matter */
    num[i++] = sum % 10 + '0';
    sum /= 10;
  }
  num[i] = 0;
  return 1 + degree(num);

}

int main(void)
{
  char num[1001];
  int sum, i;

  while (scanf("%s", num) == 1 && strcmp(num, "0")) {
    printf("%s is ", num);

    sum = 0;
    for (i = 0; num[i]; i++) {
      sum += num[i] - '0';
    }
    if (sum % 9) {
      printf("not a multiple of 9.\n");
    } else {
      printf("a multiple of 9 and has 9-degree %d.\n", degree(num));
    }
  }
  return 0;
}
