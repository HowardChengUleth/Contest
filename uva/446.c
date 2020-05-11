#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_binary(char *op)
{
  int n = strlen(op);
  int i;
  char *bin[16] = {
    "0000", "0001", "0010", "0011",
    "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
  };
  
  putchar('0');
  for (i = 0; i < 3-n; i++) {
    printf("0000");
  }
  for (i = 0; i < n; i++) {
    if (isdigit(op[i])) {
      printf("%s", bin[op[i]-'0']);
    } else {
      printf("%s", bin[op[i]-'A'+10]);
    }
  }
}

int convert(char *op)
{
  int result = 0;
  int i;

  for (i = 0; op[i]; i++) {
    result *= 16;
    if (isdigit(op[i])) {
      result += op[i] - '0';
    } else {
      result += op[i] - 'A' + 10;
    }
  }
  return result;
}

int main(void)
{
  int n;
  int num_1, num_2;
  char op1[10], op2[10], op[2];

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%s %s %s", op1, op, op2);
    print_binary(op1);
    printf(" %s ", op);
    print_binary(op2);
    printf(" = ");
    num_1 = convert(op1);
    num_2 = convert(op2);
    if (op[0] == '+') {
      printf("%d\n", num_1 + num_2);
    } else {
      printf("%d\n", num_1 - num_2);
    }
  }
  return 0;
}
