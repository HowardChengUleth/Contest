/* @JUDGE_ID: 1102NT 187 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  char no[4];
  char name[31];
} Account;

Account acct[1000];
int num_acct = 0;

typedef struct {
  char acct[4];
  int amount;
} Entry;
Entry entry[11];
int num_entry = 0;

void read_acct(void)
{
  char buffer[1024];
  int i;

  while (fgets(buffer, 1024, stdin) && strstr(buffer, "000") != buffer) {
    buffer[strlen(buffer)-1] = 0;
    for (i = 0; i < 3; i++) {
      acct[num_acct].no[i] = buffer[i];
    }
    acct[num_acct].no[i] = 0;
    strcpy(acct[num_acct].name, buffer+3);
    num_acct++;
  }
}

int find_account(char *no)
{
  int i;

  for (i = 0; i < num_acct; i++) {
    if (!strcmp(no, acct[i].no)) {
      return i;
    }
  }
  assert(0);
}

int main(void)
{
  char trans[4];
  char buffer[1024];
  int done = 0;
  int balance;
  int trans_done;
  int i, index;

  read_acct();

  fgets(buffer, 1024, stdin);
  strncpy(trans, buffer, 3);
  trans[3] = 0;
  if (!strcmp(trans, "000")) {
    done = 1;
  }

  while (!done) {
    num_entry = balance = trans_done = 0;
    strncpy(entry[num_entry].acct, buffer+3, 3);
    entry[num_entry].acct[3] = 0;
    balance += (entry[num_entry].amount = atoi(buffer+6));
    num_entry++;
    do {
      fgets(buffer, 1024, stdin);
      if (strstr(buffer, trans) == buffer) {
	strncpy(entry[num_entry].acct, buffer+3, 3);
	entry[num_entry].acct[3] = 0;
	balance += (entry[num_entry].amount = atoi(buffer+6));
	num_entry++;
      } else {
	trans_done = 1;
      }
    } while (!trans_done);
   
    if (balance) {
      printf("*** Transaction %3s is out of balance ***\n", trans);
      for (i = 0; i < num_entry; i++) {
	index = find_account(entry[i].acct);
	printf("%3s %-30s %10.2f\n", entry[i].acct, acct[index].name, 
	       entry[i].amount/100.0);
      }
      printf("%3s %-30s %10.2f\n\n", "999", "Out of Balance", -0.01*balance);
    }

    strncpy(trans, buffer, 3);
    trans[3] = 0;
    if (!strcmp(trans, "000")) {
      done = 1;
    }
  }

  return 0;
}
