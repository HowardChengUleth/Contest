/* @JUDGE_ID: 1102NT 611 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_PROC 26
#define MAX_INS 100

typedef struct {
  char block;          /* blocking or non-blocking */
  char send;           /* send or receive          */
  char who[MAX_PROC];  /* boolean array for source/dest  */
} Ins;                 /* Instruction */

typedef struct {
  char name;           /* name of processes                     */
  int num_ins;         /* number of instructions                */
  int pc;              /* program counter                       */
  int blocked;         /* is it currently blocked?              */
  Ins ins[MAX_INS];    /* set of instructions                   */
  int wait[4][MAX_PROC];
                       /* array for the list of processes it is */
                       /* waiting for                           */
  int finished;        /* when it finished                      */
} Process;

Process proc[MAX_PROC];
int proc_index[MAX_PROC];
int n;

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int cmp(const void *a, const void *b)
{
  Process *x = (Process *)a;
  Process *y = (Process *)b;
  
  return x->name - y->name;
}

void read_ins(Ins *ins)
{
  char buffer[1024], *ptr;
  int i;

  for (i = 0; i < MAX_PROC; i++) {
    ins->who[i] = 0;
  }
  scanf("%s", buffer);
  assert(strlen(buffer) == 1);
  assert(strchr("BN", buffer[0]));
  ins->block = (buffer[0] == 'B');

  scanf("%s", buffer);
  assert(strlen(buffer) == 1);
  assert(strchr("SR", buffer[0]));
  ins->send = (buffer[0] == 'S');

  fgets(buffer, 10240, stdin);
  ptr = buffer;
  while (ptr = strtok(ptr, " \n")) {
    assert(strlen(ptr) == 1);
    assert('A' <= ptr[0] && ptr[0] <= 'Z');
    assert(ins->who[ptr[0]-'A'] == 0);
    ins->who[ptr[0]-'A'] = 1;
    ptr = 0;
  }
}

void read_proc(int index)
{
  char buffer[1024];
  int i, j;

  scanf("%s", buffer);
  assert(strlen(buffer) == 1);
  assert('A' <= buffer[0] && buffer[0] <= 'Z');
  
  proc[index].name = buffer[0];
  proc_index[buffer[0]-'A'] = index;
  scanf("%d\n", &(proc[index].num_ins));
  assert(1 <= proc[index].num_ins && proc[index].num_ins <= MAX_INS);
  for (i = 0; i < proc[index].num_ins; i++) {
    read_ins(proc[index].ins+i);
  }
  proc[index].pc = proc[index].blocked = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < MAX_PROC; j++) {
      proc[index].wait[i][j] = 0;
    }
  }
  proc[index].finished = -1;
}

void simulate(void)
{
  int t, i, j, k, t1, t2, t3, temp, pc;
  int dead;
  Ins *ins;

  t = 1;
  dead = 0;

  while (!dead) {
    for (i = 0; i < n; i++) {
      if (proc[i].blocked) {
	continue;
      }
      pc = proc[i].pc;
      if (pc >= proc[i].num_ins) {
	continue;
      }
      ins = proc[i].ins+pc;
      for (j = 0; j < MAX_PROC; j++) {
	if (ins->who[j]) {
	  proc[i].wait[ins->block*2+ins->send][j]++;
	}
      }
    }

    /* determine who is blocked */
    dead = 1;
    for (i = 0; i < n; i++) {
      if (proc[i].finished > 0) {
	continue;
      }

      /* match send and receive, nonblocking first */
      for (j = 0; j < 4; j++) {
	for (k = 0; k < MAX_PROC; k++) {
	  t1 = proc_index[k];
	  t2 = proc[i].name - 'A';
	  t3 = 1-(j % 2);
	  if (proc[i].wait[j][k] && proc[t1].wait[t3][t2]) {
	    temp = min(proc[i].wait[j][k], proc[t1].wait[t3][t2]);
	    proc[i].wait[j][k] -= temp;
	    proc[t1].wait[t3][t2] -= temp;
	  }
	  t3 = 3-(j % 2);
	  if (proc[i].wait[j][k] && proc[t1].wait[t3][t2]) {
	    temp = min(proc[i].wait[j][k], proc[t1].wait[t3][t2]);
	    proc[i].wait[j][k] -= temp;
	    proc[t1].wait[t3][t2] -= temp;
	  }
	}
      }
	
      /* is it blocked? */
      proc[i].blocked = 0;
      for (k = 0; k < MAX_PROC; k++) {
	if (proc[i].wait[2][k] || proc[i].wait[3][k]) {
	  proc[i].blocked = 1;
	}
      }

      /* increment pc if not blocked */
      if (!proc[i].blocked && proc[i].pc < proc[i].num_ins) {
	proc[i].pc++;
	dead = 0;
      }

      /* if pc gone past the end, check for all nonblocking waits */
      if (proc[i].pc >= proc[i].num_ins) {
	proc[i].finished = t;
	for (k = 0; k < MAX_PROC; k++) {
	  if (proc[i].wait[0][k] || proc[i].wait[1][k]) {
	    proc[i].finished = -1;
	  }
	}
      }
    }
    t++;
  }
}

void output(void)
{
  int i, j, k;

  qsort(proc, n, sizeof(Process), cmp);
  for (i = 0; i < n; i++) {
    if (proc[i].finished > 0) {
      printf("%c finishes at t=%d\n", proc[i].name, proc[i].finished);
    } else {
      printf("%c never finishes because of", proc[i].name);
      k = 0;
      for (j = 0; j < MAX_PROC; j++) {
	if (proc[i].wait[0][j] || proc[i].wait[1][j] ||
	    proc[i].wait[2][j] || proc[i].wait[3][j]) {
	  if (k == 0) {
	    printf(" %c", j+'A');
	    k = 1;
	  } else {
	    printf(" and %c", j+'A');
	  }
	}
      }
      printf("\n");
    }
  }
}

void docase(void)
{
  int i;

  for (i = 0; i < MAX_PROC; i++) {
    proc_index[i] = -1;
  }
  scanf("%d", &n);
  assert(1 <= n && n <= MAX_PROC);
  for (i = 0; i < n; i++) {
    read_proc(i);
  }

  simulate();
  output();

}

int main(void)
{
  int T;

  scanf("%d", &T);
  while (T-- > 0) {
    docase();
    if (T > 0) {
      printf("\n");
    }
  }
  return 0;
}
