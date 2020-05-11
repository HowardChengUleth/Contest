/* @JUDGE_ID: 1102NT 10149 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int scores[13][13];
int table[64][8192];
int best[64][8192];

void score_hand(int hand[5], int scores[13])
{
  int count[7];
  int i, j, found;

  for (i = 1; i <= 6; i++) {
    count[i] = 0;
  }
  for (i = 0; i < 5; i++) {
    count[hand[i]]++;
  }

  for (i = 0; i < 13; i++) {
    scores[i] = 0;
  }

  /* sum of each kind */
  for (i = 0; i < 6; i++) {
    scores[i] = (i+1)*count[i+1];
  }
  
  /* chance */
  for (i = 0; i < 5; i++) {
    scores[6] += hand[i];
  }

  /* three/four/five of a kind */
  for (i = 1; i <= 6; i++) {
    if (count[i] >= 3) {
      scores[7] = scores[6];
      if (count[i] >= 4) {
	scores[8] = scores[6];
	if (count[i] == 5) {
	  scores[9] = 50;
	}
      }
    }
  }

  /* short straight */
  for (i = 1; i <= 3; i++) {
    found = 1;
    for (j = i; j < i+4; j++) {
      if (!count[j]) {
	found = 0;
      }
    }
    if (found) {
      scores[10] = 25;
    }
  }

  /* long straight */
  for (i = 1; i <= 2; i++) {
    found = 1;
    for (j = i; j < i+5; j++) {
      if (!count[j]) {
	found = 0;
      }
    }
    if (found) {
      scores[11] = 35;
    }
  }

  /* full house */
  if (scores[7]) {
    for (i = 1; i <= 6; i++) {
      if (count[i] == 2) {
	scores[12] = 40;
      }
    }
  }
}

int read_case(void)
{
  int hand[5];
  int i;

  for (i = 0; i < 13; i++) {
    if (scanf("%d %d %d %d %d\n", hand, hand+1, hand+2, hand+3, hand+4) != 5) {
      assert(i == 0);
      return 0;
    }
    score_hand(hand, scores[i]);
  }
  return 1;
}

void search(int cat, int sofar, int set)
{
  int sofar2, set2, bonus;
  int i, t;
  
  if (table[sofar][set] >= 0) {
    return;
  }

  /* try unused all hands */
  for (i = 0; i < 13; i++) {
    if (!(set & (1 << i))) {
      bonus = 0;
      sofar2 = (cat < 6) ? sofar + scores[i][cat] : sofar;
      if (sofar2 >= 63) {
	sofar2 = 63;
      }
      if (sofar < 63 && sofar2 == 63) {
	bonus = 35;
      }
      set2 = set | (1 << i);
      search(cat+1, sofar2, set2);
      t = table[sofar2][set2] + scores[i][cat] + bonus;
      if (t > table[sofar][set]) {
	table[sofar][set] = t;
	best[sofar][set] = i;
      }
    }
  }
}

void process_case(void)
{
  int i, j, first6, set;

  /* init table */
  for (i = 0; i < 64; i++) {
    for (j = 0; j < 8192; j++) {
      table[i][j] = -1;
    }
    table[i][8191] = 0;
  }
  
  search(0, 0, 0);

  first6 = 0;
  set = 0;
  for (i = 0; i < 13; i++) {
    j = best[first6][set];
    printf("%d ", scores[j][i]);
    set |= (1 << j);
    if (i < 6) {
      first6 += scores[j][i];
      if (first6 >= 63) {
	first6 = 63;
      }
    }
  }
  printf("%d %d\n", (first6 >= 63) ? 35 : 0, table[0][0]);
  /*
  first6 = 0;
  set = 0;
  for (i = 0; i < 13; i++) {
    j = best[first6][set];
    printf("%d %d %d\n", best[first6][set], first6, set);
    set |= (1 << j);
    if (i < 6) {
      first6 += scores[j][i];
    }
  }
  printf("\n");*/
}

int main(void)
{
  while (read_case()) {
    process_case();
  }
  return 0;
}
