#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200'000;

int64_t N, M, L;
int64_t s[MAX_N][12];
bool done[MAX_N];

void lunchtime(int64_t calls[])
{
  int left = -1, right = -1;

  int safe = 0;
  
  // move each one
  for (int i = 0; i < N; i++) {
    if (done[i]) continue;

    int64_t D = 0;
    for (int X = 1; X < 12; X++) {
      D += s[i][X] * calls[X] * X;
    }
    D = min(D, L);

    if (2*D < L) {
      // move to the left
      if (L < 4*D && left == -1) {
	left = i;
      }
    } else {
      // move to the right
      D = L-D;
      if (L < 4*D && right == -1) {
	right = i;
      } else {
	// safe
	done[i] = true;
	cout << i+1 << ' ';
	safe++;
      }
    }
  }

  if (!safe) {
    cout << "None" << endl;
  } else {
    cout << endl;
  }

  if (right >= 0) {
    cout << right+1 << endl;
    done[right] = true;
  } else if (left >= 0) {
    cout << left+1 << endl;
    done[left] = true;
  } else {
    cout << "None" << endl;
  }
}

int main()
{
  cin >> N >> M >> L;
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < 12; j++) {
      cin >> s[i][j];
    }
  }

  int64_t calls[12] = {0};
  for (int i = 0; i < M; i++) {
    int X;
    cin >> X;
    if (X != 12) {
      calls[X]++;
    } else {
      lunchtime(calls);
      fill(calls, calls+12, 0);
    }
  }

  
  return 0;
}
