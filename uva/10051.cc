#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_COLOURS = 100;

const int opp[6] = { 1, 0, 3, 2, 5, 4 };
const string name[6] = { "front", "back", "left", "right", "top", "bottom" };

int cube[500][6];

// len[i][j]  = length of longest chain with colour j on top, after processing
//              the cubes 0..i.  (0 if there is no such chain)
// top[i][j]  = the cube number (0..N-1) at the top of the chain
//              corresponding to len[i][j]
// face[i][j] = the face number corresponding to the top of the chain in
//              len[i][j]

int len[500][MAX_COLOURS+1];
int top[500][MAX_COLOURS+1];
int face[500][MAX_COLOURS+1];

void print_soln(int i, int c, int N)
{
  if (i == N) return;

  if (top[i][c] == i) {
    cout << i+1 << ' ' << name[face[i][c]] << endl;
    c = cube[i][opp[face[i][c]]];
  }
  print_soln(i+1, c, N);
}

void solve(int N)
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 6; j++) {
      cin >> cube[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 1; j <= MAX_COLOURS; j++) {
      len[i][j] = 0;
    }
  }

  // start the last row
  for (int j = 0; j < 6; j++) {
    int c = cube[N-1][j];
    len[N-1][c] = 1;
    top[N-1][c] = N-1;
    face[N-1][c] = j;
  }

  // do the remaining rows
  for (int i = N-2; i >= 0; i--) {
    // copy the previous row
    for (int c = 1; c <= MAX_COLOURS; c++) {
      if (len[i+1][c] > 0) {
	len[i][c] = len[i+1][c];
	top[i][c] = top[i+1][c];
	face[i][c] = face[i+1][c];
      }
    }

    for (int j = 0; j < 6; j++) {
      int c = cube[i][j];
      int bot = cube[i][opp[j]];

      int newlen = len[i+1][bot] + 1;
      if (newlen > len[i][c]) {
	len[i][c] = newlen;
	top[i][c] = i;
	face[i][c] = j;
      }
    }
  }

  int best_c = max_element(len[0]+1, len[0]+MAX_COLOURS+1)
    - len[0];

  cout << len[0][best_c] << endl;
  print_soln(0, best_c, N);
}

int main(void)
{
  int N;
  int case_num = 1;
  while (cin >> N && N > 0) {
    if (case_num > 1) {
      cout << endl;
    }
    cout << "Case #" << case_num++ << endl;
    solve(N);
  }
  return 0;
}
