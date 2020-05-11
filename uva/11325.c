/*
 * The idea is this: if we know when we want to play ties, then all we
 * have to do is to match up the cards at the ties, ignore the cards
 * we throw away, and make sure that we can beat every one of the other
 * cards.
 *
 * We try all possible places to put ties.  There are not many
 * because once we have a tie we reduce the size of the hand by 4
 * (the tie + 3 more cards).  The recurrence relation to count the
 * number of different "tie schedules" is f(n) = f(n-1) + f(n-4)
 * and you can show that this does not get too large for n = 26.
 *
 * Once we have a tie schedule, the cards to play at the ties are
 * fixed.  For all the other cards, we can greedily rearrange our
 * cards: pick the least remaining card that beats it.  If we can
 * do this for all the other cards, we are done.  Otherwise, we can
 * prove that there is no way to do it for the tie schedule.
 *
 */

#include <stdio.h>
#include <string.h>

int gen_ties(const int *myhand, const int *hand, char *ties, int i)
{
  int next;
  int k, j;
  int temp_hand[13];

  if (i == 25) {
    for (k = 0; k < 13; k++) {
      temp_hand[k] = myhand[k];
    }

    /* do all the ties first */
    for (k = 0; k < 26; k++) {
      if (ties[k]) {
	/* can't do the ties */
	if (!temp_hand[hand[k]]) {
	  return 0;
	} else {
	  temp_hand[hand[k]]--;
	}
      }
    }

    /* now greedy choose the non-ties */
    for (k = 0; k < 26; k++) {
      if (ties[k]) {
	for (j = 0; j < 3 && k < 24; j++) {
	  k++;
	}
	continue;
      }
      for (j = hand[k]+1; j < 13 && !temp_hand[j]; j++)
	;
      if (j >= 13) return 0;
      temp_hand[j]--;
    }

    return 1;
  }

  /* try no ties */
  if (gen_ties(myhand, hand, ties, i+1)) {
    return 1;
  }

  /* try a tie here */
  ties[i] = 1;
  next = i+4;
  if (next >= 25) {
    next = 25;        /* make sure we have one card left */
  }
  if (gen_ties(myhand, hand, ties, next)) {
    return 1;
  }
  ties[i] = 0;
  
  return 0;
}

void solve_case(void)
{
  int hand[26];
  char card[3];
  int i;
  char *rank = "23456789TJQKA";
  int myhand[13];
  char ties[26];

  for (i = 0; i < 13; i++) {
    myhand[i] = 4;
  }

  for (i = 0; i < 26; i++) {
    scanf("%s", card);
    hand[i] = strchr(rank, card[0]) - rank;
    myhand[hand[i]]--;
    ties[i] = 0;
  }
  printf("%s\n", (gen_ties(myhand, hand, ties, 0) ? "yes" : "no"));
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
  }
  
  return 0;
}
