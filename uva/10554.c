/* @JUDGE_ID: 1102NT 10554 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int cal[5] = {9,4,4,4,7};

void process(char *buffer, double *fatC, double *totalC)
{
  double c[5];
  char type[5];
  int amount[5];
  char *p;
  int i;
  double total = 0.0, total_perc = 0.0;
  
  p = buffer;
  for (i = 0; i < 5; i++) {
    p = strtok(p, " \n");
    amount[i] = atoi(p);
    type[i] = p[strlen(p)-1];
    p = 0;
  }

  for (i = 0; i < 5; i++) {
    if (type[i] == 'g') {
      c[i] = amount[i]*cal[i];
      total += c[i];
    } else if (type[i] == 'C') {
      c[i] = amount[i];
      total += c[i];
    } else {
      assert(type[i] == '%');
      total_perc += amount[i];
    }
  }

  total = total*100.0/(100.0-total_perc);
  for (i = 0; i < 5; i++) {
    if (type[i] == '%') {
      c[i] = (amount[i]/100.00)*total;
    }
  }

  *fatC += c[0];
  *totalC += total;
}

int main(void)
{
  char buffer[1024];
  double fatC, totalC;

  while (fgets(buffer, 1024, stdin) && strcmp(buffer, "-\n")) {
    fatC = totalC = 0.0;
    process(buffer, &fatC, &totalC);
    while (fgets(buffer, 1024, stdin) && strcmp(buffer, "-\n")) {
      process(buffer, &fatC, &totalC);
    }
    printf("%.0f%%\n", fatC*100.0/totalC);
  }
  
  return 0;
}
