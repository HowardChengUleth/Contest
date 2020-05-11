/* @JUDGE_ID: 1102NT 706 C "" */

#include <stdio.h>
#include <stdlib.h>

char lcd[50][200];

/*                     The segments are numbered
     -                           0
    | |                         1 2
     -                           3
    | |                         4 5
     -                           6
*/

char segs[10][7] = {
  {1,1,1,0,1,1,1},
  {0,0,1,0,0,1,0},
  {1,0,1,1,1,0,1},
  {1,0,1,1,0,1,1},
  {0,1,1,1,0,1,0},
  {1,1,0,1,0,1,1},
  {1,1,0,1,1,1,1},
  {1,0,1,0,0,1,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};
     
void fill(int d, int s, int c)
{
  int i;

  if (segs[d][0]) {
    for (i = 1; i <= s; i++) {
      lcd[0][c+i] = '-';
    }
  }

  if (segs[d][1]) {
    for (i = 1; i <= s; i++) {
      lcd[i][c] = '|';
    }
  }
    
  if (segs[d][2]) {
    for (i = 1; i <= s; i++) {
      lcd[i][c+s+1] = '|';
    }
  }
  
  if (segs[d][3]) {
    for (i = 1; i <= s; i++) {
      lcd[s+1][c+i] = '-';
    }
  }
  
  if (segs[d][4]) {
    for (i = 1; i <= s; i++) {
      lcd[i+s+1][c] = '|';
    }
  }
  
  if (segs[d][5]) {
    for (i = 1; i <= s; i++) {
      lcd[i+s+1][c+s+1] = '|';
    }
  }
  
  if (segs[d][6]) {
    for (i = 1; i <= s; i++) {
      lcd[2*s+2][c+i] = '-';
    }
  }


}

int main(void)
{
  int s, i, j;
  char digits[10];

  while (scanf("%d %s", &s, digits) == 2 && !(s == 0 && digits[0] == '0'
					      && digits[1] == 0)) {
    for (i = 0; i < 2*s+3; i++) {
      for (j = 0; j < 200; j++) {
	lcd[i][j] = ' ';
      }
    }
   
    for (i = 0; digits[i]; i++) {
      fill(digits[i]-'0', s, i*(s+2+1));
    }
    for (j = 0; j < 2*s+3; j++) {
      lcd[j][i*(s+2+1)-1] = 0;
    }
    for (i = 0; i < 2*s+3; i++) {
      printf("%s\n", lcd[i]);
    }
    printf("\n");
  }
  return 0;
}
