/* @JUDGE_ID: 1102NT 608 C "" */


/*
 * Solution to "Counterfeit Dollar"
 *
 * Author: Howard Cheng
 * Date: Nov 10, 1998
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM 12
enum {EVEN, LIGHT, HEAVY, UNKNOWN};

int status[NUM];

void process(char *str1, char *str2, char *res)
{
  int n1, n2, i, c;
  int mark[NUM];

  n1 = strlen(str1);
  n2 = strlen(str2);
  assert(n1 == n2);

  for (i = 0; i < NUM; i++) {
    mark[i] = 0;
  }

  for (i = 0; i < n1; i++) {
    c = str1[i] - 'A';
    mark[c] = 1;
    if (status[c] == EVEN) {
      continue;
    }
    if (status[c] == LIGHT && !strcmp(res, "up")) {
      status[c] = EVEN;
    } else if (status[c] == HEAVY && !strcmp(res, "down")) {
      status[c] = EVEN;
    } else if (!strcmp(res, "even")) {
      status[c] = EVEN;
    } else if (status[c] == UNKNOWN && !strcmp(res, "up")) {
      status[c] = HEAVY;
    } else if (status[c] == UNKNOWN && !strcmp(res, "down")) {
      status[c] = LIGHT;
    }
  }

  for (i = 0; i < n2; i++) {
    c = str2[i] - 'A';
    mark[c] = 1;
    if (status[c] == EVEN) {
      continue;
    }
    if (status[c] == LIGHT && !strcmp(res, "down")) {
      status[c] = EVEN;
    } else if (status[c] == HEAVY && !strcmp(res, "up")) {
      status[c] = EVEN;
    } else if (!strcmp(res, "even")) {
      status[c] = EVEN;
    } else if (status[c] == UNKNOWN && !strcmp(res, "down")) {
      status[c] = HEAVY;
    } else if (status[c] == UNKNOWN && !strcmp(res, "up")) {
      status[c] = LIGHT;
    }
  }

  if (strcmp(res, "even")) {
    for (i = 0; i < NUM; i++) {
      if (!mark[i]) {
        status[i] = EVEN;
      }
    }
  }

}

int main(void)
{
  int n, i;
  char str1[1024], str2[1024], res[1024];
  int coin;
  char ans[1024];

  scanf("%d", &n);
  while (n-- > 0) {
    for (i = 0; i < NUM; i++) {
      status[i] = UNKNOWN;
    }
    for (i = 0; i < 3; i++) {
      scanf("%s %s %s", str1, str2, res);
      process(str1, str2, res);
    }
    coin = -1;
    for (i = 0; i < NUM; i++) {
      if (status[i] == HEAVY) {
        assert(coin == -1);
        coin = i;
        strcpy(ans, "heavy");
      } else if (status[i] == LIGHT) {
        assert(coin == -1);
        coin = i;
        strcpy(ans, "light");
      } else {
        assert(status[i] == EVEN || status[i] == UNKNOWN);
      }
    }

    assert(coin >= 0);
    printf("%c is the counterfeit coin and it is %s.\n", 'A'+coin, ans);
  }

  return 0;
}
