#include <stdio.h>

int rate[5][24*60];

int charges[5][3] = {
  { 10,  6,  2 },
  { 25, 15,  5 },
  { 53, 33, 13 },
  { 87, 47, 17 },
  { 144, 80, 30}};

int category(int m)
{
  if (8*60 <= m && m < 18*60) {
    return 0;
  } else if (18*60 <= m && m < 22*60) {
    return 1;
  } else {
    return 2;
  }
}

void fill_table(void)
{
  int i, j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 24*60; j++) {
      rate[i][j] = charges[i][category(j)];
    }
  }
}

int main(void)
{
  char step;
  char num[1024];
  int s_h, s_m, e_h, e_m;
  int start, end;
  int cost;
  int min[3];

  fill_table();
  while (scanf("%c", &step) == 1 && step != '#') {
    scanf("%s %d %d %d %d\n", num, &s_h, &s_m, &e_h, &e_m);
    start = s_h*60 + s_m;
    end = e_h*60 + e_m;
    cost = min[0] = min[1] = min[2] = 0;

    cost += rate[step-'A'][start];
    min[category(start)]++;
    if (++start >= 24*60) {
      start = 0;
    }

    while (start != end) {
      cost += rate[step-'A'][start];
      min[category(start)]++;

      if (++start >= 24*60) {
	start = 0;
      }
    }
    printf("%10s%6d%6d%6d%3c%8.2f\n", num, min[0], min[1], min[2], 
	   step, cost/100.0);
  }
  return 0;
}
