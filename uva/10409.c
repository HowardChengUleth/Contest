#include <stdio.h>

int die[6]; /* top, bot, N, S, W, E */

void init_die(void)
{
  die[0] = 1; die[1] = 6;
  die[2] = 2; die[3] = 5;
  die[4] = 3; die[5] = 4;
}
 
void north(void)
{
  int temp = die[0];
  die[0] = die[3];
  die[3] = die[1];
  die[1] = die[2];
  die[2] = temp;
}

void south(void)
{
  north();
  north();
  north();
}

void west(void)
{
  int temp = die[0];
  die[0] = die[5];
  die[5] = die[1];
  die[1] = die[4];
  die[4] = temp;
}

void east(void)
{
  west();
  west();
  west();
}

int main(void)
{
  int n;
  char cmd[10];

  while (scanf("%d", &n) == 1 && n) {
    init_die();
    while (n-- > 0) {
      scanf("%s", cmd);
      switch (cmd[0]) {
      case 'n':
	north();
	break;
      case 's':
	south();
	break;
      case 'e':
	east();
	break;
      case 'w':
	west();
	break;
      }
    }
    printf("%d\n", die[0]);
  }
  return 0;
}
