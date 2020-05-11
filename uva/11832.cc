#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 40;
const int MAX_T = 1000;
const int MAX_TOTAL = MAX_N * MAX_T;

unsigned long long pos[2][MAX_TOTAL+1];
unsigned long long neg[2][MAX_TOTAL+1];

bool docase()
{
  int N, F;
  cin >> N >> F;
  if (N == 0 && F == 0) {
    return false;
  }

  assert(2 <= N && N <= MAX_N);

  bool negF = (F < 0);
  if (negF) {
    F = -F;
  }

  int T[40];
  for (int i = 0; i < N; i++) {
    cin >> T[i];
    assert(1 <= T[i] && T[i] <= MAX_T);
  }

  int total = 0;
  int curr_row = 0;

  // let's do the first amount
  fill(pos[0], pos[0] + total + T[0] + 1, 0);
  fill(neg[0], neg[0] + total + T[0] + 1, 0);
  pos[0][T[0]] |= 1;
  total = T[0];

  for (int i = 1; i < N; i++) {
    int next_row = 1 - curr_row;
    fill(pos[next_row], pos[next_row] + total + T[i] + 1, 0);
    fill(neg[next_row], neg[next_row] + total + T[i] + 1, 0);

    for (int j = 0; j <= total; j++) {
      // can't make amount j
      if (!pos[curr_row][j] && !neg[curr_row][j]) continue;

      // try adding T[i]
      int next_amount = j + T[i];
      pos[next_row][next_amount] |= pos[curr_row][j] | (1ULL << i);
      neg[next_row][next_amount] |= neg[curr_row][j];

      // try subtracting T[i];
      next_amount = j - T[i];
      if (next_amount >= 0) {
	pos[next_row][next_amount] |= pos[curr_row][j];
	neg[next_row][next_amount] |= neg[curr_row][j] | (1ULL << i);
      } else {
	// need to flip
	pos[next_row][-next_amount] |= neg[curr_row][j] | (1ULL << i);
	neg[next_row][-next_amount] |= pos[curr_row][j];
      }
    }

    total += T[i];
    curr_row = next_row;
  }

  if (F > total || (pos[curr_row][F] == 0 && neg[curr_row][F] == 0)) {
    cout << "*" << endl;
  } else {
    for (int i = 0; i < N; i++) {
      bool ispos = pos[curr_row][F] & (1ULL << i);
      bool isneg = neg[curr_row][F] & (1ULL << i);
      if (negF) {
	swap(ispos, isneg);
      }
      if (ispos && isneg || F == 0) {
	cout << '?';
      } else if (ispos) {
	cout << '+';
      } else if (isneg) {
	cout << '-';
      } else {
	assert(false);
      }
    }
    cout << endl;
  }
  return true;
}

int main(void)
{
  while (docase())
    ;
  return 0;
}
