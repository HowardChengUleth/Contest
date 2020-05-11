#include <stdio.h>
#include <string.h>
#include <ctype.h>

char deck[52][3];

int last_pile;

int value(char c)
{
  if (isdigit(c)) {
    return c - '0';
  } else if (c == 'T') {
    return 10;
  } else if (c == 'A') {
    return 1;
  }
  return -1;
}

void find_pair(char top[16][3], int *pair1, int *pair2)
{
  int i, j;
  int vi, vj;

  for (i = 0; i < last_pile; i++) {
    vi = value(top[i][0]);
    if (vi < 0) continue;
    for (j = i+1; j < last_pile; j++) {
      vj = value(top[j][0]);
      if (vj < 0 || vi+vj != 11) continue;
      *pair1 = i;
      *pair2 = j;
      return;
    }
  }
  *pair1 = *pair2 = -1;
}

void find_trip(char top[16][3], int *trip1, int *trip2, int *trip3)
{
  int i, j, k;
  int seen[256];

  for (i = 0; i < last_pile; i++) {
    for (j = i+1; j < last_pile; j++) {
      for (k = j+1; k < last_pile; k++) {
	seen['J'] = seen['Q'] = seen['K'] = 0;
	seen[top[i][0]] = seen[top[j][0]] = seen[top[k][0]] = 1;
	if (seen['J'] && seen['Q'] && seen['K']) {
	  *trip1 = i;
	  *trip2 = j;
	  *trip3 = k;
	  return;
	}
      }
    }
  }
  *trip1 = *trip2 = *trip3 = -1;
}

void process_deck(int num)
{
  int pile[16];
  char top[16][3];
  int i, k;
  int pair1, pair2;
  int trip1, trip2, trip3;

  last_pile = 0;

  printf("%3d:", num);
  for (i = 0; i < 16; i++) {
    pile[i] = 0;
  }

  k = 0;
  while (k < 52) {
    find_pair(top, &pair1, &pair2);
    find_trip(top, &trip1, &trip2, &trip3);

    if (pair1 >= 0 && trip1 >= 0) {
      if (pair1 < trip1) {
	trip1 = -1;
      } else {
	pair1 = -1;
      }
    }

    if (pair1 >= 0) {
      strcpy(top[pair1], deck[k++]);
      pile[pair1]++;

      if (k < 52) {
	strcpy(top[pair2], deck[k++]);
	pile[pair2]++;
      }
    } else if (trip1 >= 0) {
      strcpy(top[trip1], deck[k++]);
      pile[trip1]++;

      if (k < 52) {
	strcpy(top[trip2], deck[k++]);
	pile[trip2]++;
      }
      if (k < 52) {
	strcpy(top[trip3], deck[k++]);
	pile[trip3]++;
      }
    } else {
      if (last_pile < 16) {
	strcpy(top[last_pile], deck[k++]);
	pile[last_pile]++;
	last_pile++;
      } else {
	printf(" Overflowed on card no %d\n", k+1);
	return;
      }
    }
  }
  for (i = 0; i < last_pile; i++) {
    printf("%3d", pile[i]);
  }
  printf("\n");
}

int main(void)
{
  int i;
  int deck_no = 1;

  while (scanf("%s", deck[0]) == 1 && deck[0][0] != '#') {
    for (i = 1; i < 52; i++) {
      scanf("%s", deck[i]);
    }
    process_deck(deck_no++);
  }
  return 0;
}
