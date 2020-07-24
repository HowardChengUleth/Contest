#include <bits/stdc++.h>

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//
//

char block[100][100];
int N, S, A;
int streets[100];

// friendly[i][j] = number of ridings from avenues i to j-1 that contains
// at least one friendly neigbourhoods, if there are no boundaries inside
int friendly[101][101];

// F[i][j] = max number of friendly ridings from avenue 1 to i-1, with
// j boundaries
int F[101][101];

// remembers the choice that led to the optimal above
int best_j[101][101];



void compute_friendly()
{
  int count[101][101];
  int i, j, s, t;
  int area, good;

  // count[i][s] = number of friendly neighbourhoods between avenues i and i+1,
  // between streets streets[s] to streets[s+1]-1
  for (i = 1; i < 100; i++) {
    for (s = 0; s < S-1; s++) {
      count[i][s] = 0;
      for (j = streets[s]; j < streets[s+1]; j++) {
	if (block[i][j]) {
	  count[i][s]++;
	}
      }
    }
  }

  for (i = 1; i <= 100; i++) {
    friendly[i][i] = 0;
    for (j = i+1; j <= 100; j++) {
      friendly[i][j] = 0;
      for (s = 0; s < S-1; s++) {
	good = 0;
	for (t = i; t < j; t++) {
	  good += count[t][s];
	}
	if (good > 0) {
	  friendly[i][j]++;
	}
      }
    }
  }
}

void compute_F(void)
{
  int n, a, j;

  for (n = 2; n <= 100; n++) {
    F[n][2] = friendly[1][n];
    best_j[n][2] = -1;
  }
  for (a = 3; a <= A; a++) {
    for (n  = 0; n <= 100; n++) {
      if (a > n) {
	F[n][a] = -1;
	best_j[n][a] = -1;
      } else {
	F[n][a] = -1;
	best_j[n][a] = -1;
	for (j = 2; j < n; j++) {
	  if (F[j][a-1] != -1 && F[j][a-1] + friendly[j][n] > F[n][a]) {
	    F[n][a] = F[j][a-1] + friendly[j][n];
	    best_j[n][a] = j;
	  }
	}
      }
    }
  }
}

void print_soln(void)
{
  int soln[100], n = 0;
  int i = 100, k = A;

  while (k > 1) {
    soln[n++] = i;
    i = best_j[i][k--];
  }
  soln[n++] = 1;

  cout << A << endl;
  for (i = n-1; i >= 0; i--) {
    cout << ' ' << soln[i];
  }
  cout << endl;
}

void solve()
{  
  for (int i = 0; i < 100; i++) {
    fill(block[i], block[i]+100, 0);
    }
  
  for (int k = 0; k < N; k++) {
    int s, a;
    cin >> s >> a;
    block[a][s] = 1;
  }
  cin >> S;
  for (int k = 0; k < S; k++) {
    cin >> streets[k];
  }
  cin >> A;
  
  compute_friendly();
  compute_F();
  print_soln();
}

int main()
{
  ios::sync_with_stdio(false);
  while (cin >> N && N != -1) {
    solve();
  }
  return 0;
}

