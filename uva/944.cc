#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int happy_count[100000];
bool is_init[100000];

int happy(int N)
{
  set<int> S;
  int sum;
  int count = 0;

  while (N >= 100000 || !is_init[N]) {
    S.insert(N);
    sum = 0;
    while (N > 0) {
      sum += (N % 10) * (N % 10);
      N /= 10;
    }
    if (S.find(sum) != S.end()) {
      return -1;
    }
    N = sum;
    count++;
  }

  if (N  < 100000 && is_init[N]) {
    if (happy_count[N] < 0) {
      return -1;
    } else {
      return count + happy_count[N];
    }
  } else {
    return count;
  }
}

int main(void)
{
  fill(is_init, is_init+100000, false);

  happy_count[1] = 1;
  is_init[1] = true;

  for (int i = 2; i <= 99999; i++) {
    happy_count[i] = happy(i);
    is_init[i] = true;
  }

  int L, H;
  bool first = true;
  while (cin >> L >> H) {
    if (!first) {
      cout << endl;
    }
    first = false;
    while (L <= H) {
      if (happy_count[L] >= 0) {
	cout << L << ' ' << happy_count[L] << endl;
      }
      L++;
    }
  }

  return 0;
}
