#include <stdio.h>
#include <stdlib.h>

int reg[10];
int ram[1000];

void read_mem(void)
{
  char line[100];
  int i;

  for (i = 0; i < 10; i++) {
    reg[i] = 0;
  }
  for (i = 0; i < 1000; i++) {
    ram[i] = 0;
  }

  for (i = 0; fgets(line, 1000, stdin) && line[0] != '\n'; i++) {
    ram[i] = atoi(line);
  }
}

int execute(int *pc)
{
  int d1, d2, d3;
  int ins = ram[*pc];

  d3 = ins % 10;
  d2 = (ins / 10) % 10;
  d1 = ins / 100;

  switch (d1) {
  case 1:    /* halt */
    return 0;
  case 2:
    reg[d2] = d3;
    (*pc)++;
    break;
  case 3:
    reg[d2] = (reg[d2] + d3) % 1000;
    (*pc)++;
    break;
  case 4:
    reg[d2] = (reg[d2] * d3) % 1000;
    (*pc)++;
    break;
  case 5:
    reg[d2] = reg[d3];
    (*pc)++;
    break;
  case 6:
    reg[d2] = (reg[d2] + reg[d3]) % 1000;
    (*pc)++;
    break;
  case 7:
    reg[d2] = (reg[d2] * reg[d3]) % 1000;
    (*pc)++;
    break;
  case 8:
    reg[d2] = ram[reg[d3]];
    (*pc)++;
    break;
  case 9:
    ram[reg[d3]] = reg[d2];
    (*pc)++;
    break;
  case 0:
    if (reg[d3]) {
      *pc = reg[d2];
    } else {
      (*pc)++;
    }
    break;
  }


  return 1;
}

void do_case(void)
{
  int pc = 0;
  int num = 0;

  read_mem();

  do {
    num++;
  } while (execute(&pc));
  printf("%d\n", num);
}

int main(void)
{
  int N;

  scanf("%d\n", &N);

  while (N-- > 0) {
    do_case();
    if (N > 0) {
      printf("\n");
    }
  }

  return 0;
}
