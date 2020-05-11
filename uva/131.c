#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef char Card[3];
Card hand[5], deck[5];

typedef enum {
   ONE, TWO, TWOPAIR, THREE, STRAIGHT, FLUSH, FULL, FOUR, SFLUSH
} Rank;

char *response[9] = {
   "highest-card", "one-pair", "two-pairs", "three-of-a-kind",
   "straight", "flush", "full-house", "four-of-a-kind",
   "straight-flush"
};

int read_cards(void)
{
   int i;

   if (scanf("%s", hand[0]) != 1) {
      return 0;
   }
   printf("Hand: %s ", hand[0]);
   for (i = 1; i < 5; i++) {
      scanf("%s", hand[i]);
      printf("%s ", hand[i]);
   }
   printf("Deck: ");
   for (i = 0; i < 5; i++) {
      scanf("%s", deck[i]);
      printf("%s ", deck[i]);
   }
   return 1;
}

char get_suit(Card c)
{
   return c[1];
}

int get_val(Card c)
{
   if (isdigit(c[0])) {
      return c[0] - '0' - 1;
   } else if (c[0] == 'A') {
      return 13;
   } else if (c[0] == 'K') {
      return 12;
   } else if (c[0] == 'Q') {
      return 11;
   } else if (c[0] == 'J') {
      return 10;
   } else if (c[0] == 'T') {
      return 9;
   } else {
      printf("Card = %s\n", c);
      printf("character = %c\n", c[0]);
      exit(1);
      return -1;
   }
}

int get_count(Card h[5])
{
   int count[14];
   int i, maxc;

   for (i = 0; i < 14; i++) {
      count[i] = 0;
   }
   for (i = 0; i < 5; i++) {
      count[get_val(h[i])]++;
   }
   maxc = 0;
   for (i = 0; i < 14; i++) {
      if (count[i] > maxc) {
         maxc = count[i];
      }
   }
   return maxc;
}

int check_str(Card h[5])
{
   int seen[14];
   int i, t;

   for (i = 0; i < 14; i++) {
      seen[i] = 0;
   }
   for (i = 0; i < 5; i++) {
      t = get_val(h[i]);
      seen[t] = 1;
      if (t == 13) {
         seen[0] = 1;
      }
   }
   i = 0;
   while (!seen[i]) {
      i++;
   }
   for (t = 1; t < 5; t++) {
      if (!seen[i+t]) {
         break;
      }
   }
   if (t == 5) {
      return 1;
   }

   /* search the other way */
   i = 13;
   while (!seen[i]) {
      i--;
   }
   for (t = 1; t < 5; t++) {
      if (!seen[i-t]) {
         return 0;
      }
   }
   return 1;
}

int check_flush(Card h[5])
{
   char suit;
   int i;

   suit = get_suit(h[0]);
   for (i = 1; i < 5; i++) {
      if (suit != get_suit(h[i])) {
         return 0;
      }
   }
   return 1;
}

int check_sflush(Card h[5])
{
   return (check_flush(h) && check_str(h));
}

int check_full(Card h[5])
{
   int count[14];
   int i, seen2, seen3;

   for (i = 0; i < 14; i++) {
      count[i] = 0;
   }
   for (i = 0; i < 5; i++) {
      count[get_val(h[i])]++;
   }
   seen2 = seen3 = 0;
   for (i = 0; i < 14; i++) {
      if (count[i] == 2) {
         seen2 = 1;
      } else if (count[i] == 3) {
         seen3 = 1;
      }
   }
   return (seen2 && seen3);
}

int check_2pair(Card h[5])
{
   int count[14];
   int i, seen2;

   for (i = 0; i < 14; i++) {
      count[i] = 0;
   }
   for (i = 0; i < 5; i++) {
      count[get_val(h[i])]++;
   }
   seen2 = 0;
   for (i = 0; i < 14; i++) {
      if (count[i] == 2) {
         seen2++;
      }
   }
   return (seen2 == 2);
}


Rank calc_rank(Card h[5], Rank best)
{
   Rank curr;
   int done = 0;

   curr = SFLUSH;
   while (curr > best && !done) {
      switch (curr) {
      case SFLUSH:
         if (check_sflush(h)) {
            done = 1;
         }
         break;
      case FOUR:
         if (get_count(h) == 4) {
            done = 1;
         }
         break;
      case FULL:
         if (check_full(h)) {
            done = 1;
         }
         break;
      case FLUSH:
         if (check_flush(h)) {
            done = 1;
         }
         break;
      case STRAIGHT:
         if (check_str(h)) {
            done = 1;
         }
         break;
      case THREE:
         if (get_count(h) == 3) {
            done = 1;
         }
         break;
      case TWOPAIR:
         if (check_2pair(h)) {
            done = 1;
         }
         break;
      case TWO:
         if (get_count(h) == 2) {
            done = 1;
         }
         break;
      default:
         fprintf(stderr, "Unhandled case\n");
         exit(-1);
      }
      if (!done) {
         curr--;
      }
   }
   return curr;
}

void calc_best(void)
{
   Rank best, rank;
   Card th1[5], th2[5];
   int i, j, k, l, m;

   /* check with zero or five replacements */
   best = calc_rank(hand, ONE);
   best = calc_rank(deck, best);

   /* check with one or four replacements */
   for (i = 0; i < 4; i++) {
      strcpy(th2[i], deck[i]);
   }
   for (i = 0; i < 5; i++) {
      for (j = 0; j < 5; j++) {
         if (i != j) {
            strcpy(th1[j], hand[j]);
         } else {
            strcpy(th1[j], deck[0]);
         }
      }
      strcpy(th2[4], hand[i]);
      best = calc_rank(th1, best);
      best = calc_rank(th2, best);
   }

   /* check with two or three replacements */
   for (i = 0; i < 2; i++) {
      strcpy(th1[i], deck[i]);
      strcpy(th2[i], deck[i]);
   }
   strcpy(th2[2], deck[2]);
   for (i = 0; i < 5; i++) {
      for (j = i+1; j < 5; j++) {
         l = 2;
         m = 3;
         for (k = 0; k < 5; k++) {
            if (k != i && k != j) {
               strcpy(th1[l++], hand[k]);
            } else {
               strcpy(th2[m++], hand[k]);
            }
         }
         assert(l == 5 && m == 5);
         best = calc_rank(th1, best);
         best = calc_rank(th2, best);
      }
   }

   printf("Best hand: %s\n", response[best]);
}

int main(void)
{
   while (read_cards()) {
      calc_best();
   }
   return 0;
}
