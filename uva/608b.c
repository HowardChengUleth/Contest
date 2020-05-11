/* @JUDGE_ID: 1102NT 608 C "" */

#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
  char left[7], right[7], result[5];
} Weighing;

Weighing weighing[3];
int weights[12];  /* -1 for light, 0 for normal, 1 for heavy */

/* see if weights are consistent with the k-th weighing */
int okay_weighing(int k)
{
  int lhs, rhs, i;

  lhs = rhs = 0;
  for (i = 0; i < strlen(weighing[k].left); i++) {
    lhs += weights[weighing[k].left[i]-'A'];
    rhs += weights[weighing[k].right[i]-'A'];
  }
  return ((lhs == rhs && !strcmp(weighing[k].result, "even")) ||
	  (lhs < rhs && !strcmp(weighing[k].result, "down")) ||
	  (lhs > rhs && !strcmp(weighing[k].result, "up")));
}

int okay(void)
{
  return okay_weighing(0) && okay_weighing(1) && okay_weighing(2);
}

int main(void)
{
  int n, i;

  scanf("%d", &n);
  while (n-- > 0) {
    for (i = 0; i < 3; i++) {
      scanf("%s %s %s", weighing[i].left, weighing[i].right, 
	    weighing[i].result);
    }
    for (i = 0; i < 12; i++) {
      weights[i] = 0;
    }
    for (i = 0; i < 12; i++) {
      weights[i] = -1;   /* try light */
      if (okay()) {      /* consistent weight assignment: done */
	break;
      }
      weights[i] = 1;    /* try heavy */
      if (okay()) {      /* consistent weight assignment: done */
	break;
      }
      weights[i] = 0;
    }
    assert(i < 12 && weights[i] != 0);      /* found one */
    printf("%c is the counterfeit coin and it is %s.\n", 'A'+i,
	   (weights[i] < 0) ? "light" : "heavy");
  }

  return 0;
}
