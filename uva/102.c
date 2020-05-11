/* @JUDGE_ID: 1102NT 102 C "Brute Force" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_BINS 3

typedef struct {
  int b,g,c;
} Bin;

static int read_bins(Bin bin[NUM_BINS]);
static void process(Bin bin[NUM_BINS]);
static int num_move(Bin bin[NUM_BINS], char *assign);

int main(void)
{
  Bin bins[NUM_BINS];
  
  while (read_bins(bins)) {
    process(bins);
  }

  return 0;
}

/* read data into the structure, return 1 if successful, 0 if EOF */
static int read_bins(Bin bin[NUM_BINS])
{
  int error = 0;
  int i;
  
  for (i = 0; i < NUM_BINS && !error; i++) {
    error = (scanf("%d %d %d", &(bin[i].b), &(bin[i].g), &(bin[i].c)) != 3);
  }
  return !error;
}

/* find the optimal movement and print */
static void process(Bin bin[NUM_BINS])
{
  int bot_moved;
  char *best_assign;
  int temp;

  /* try all 6 permutations */
  /* note that the alphabetical ordering is automatically taken care of */
  bot_moved = num_move(bin, "BCG");
  best_assign = "BCG";

  temp = num_move(bin, "BGC");
  if (temp < bot_moved) {
    bot_moved = temp;
    best_assign = "BGC";
  }

  temp = num_move(bin, "CBG");
  if (temp < bot_moved) {
    bot_moved = temp;
    best_assign = "CBG";
  }

  temp = num_move(bin, "CGB");
  if (temp < bot_moved) {
    bot_moved = temp;
    best_assign = "CGB";
  }

  temp = num_move(bin, "GBC");
  if (temp < bot_moved) {
    bot_moved = temp;
    best_assign = "GBC";
  }

  temp = num_move(bin, "GCB");
  if (temp < bot_moved) {
    bot_moved = temp;
    best_assign = "GCB";
  }

  printf("%s %d\n", best_assign, bot_moved);
}

/* find number of bottles to move given the bin assignment */
static int num_move(Bin bin[NUM_BINS], char *assign)
{
  int sum = 0;
  int i;

  for (i = 0; i < NUM_BINS; i++) {
    if (assign[i] == 'B') {
      sum += bin[i].c + bin[i].g;
    } else if (assign[i] == 'C') {
      sum += bin[i].b + bin[i].g;
    } else if (assign[i] == 'G') {
      sum += bin[i].b + bin[i].c;
    } else {
      fprintf(stderr, "Big trouble in num_move\n");
      exit(1);
    }    
  }
  return sum;
}





