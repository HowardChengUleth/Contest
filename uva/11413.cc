#include <iostream>
#include <numeric>

using namespace std;

bool possible(int n, int m, int c[], int mid)
{
  int m_count = 1;
  int amt = 0;
  int i = 0;

  while (i < n && m_count <= m) {
    if (amt + c[i] > mid) {
      m_count++;
      amt = 0;
    } else {
      amt += c[i++];
    }
  }

  return m_count <= m;
}

int main(void)
{
  int n, m;
  while (cin >> n >> m) {
    int c[1000];
    for (int i = 0; i < n; i++) {
      cin >> c[i];
    }

    int hi = accumulate(c, c+n, 0);     // possible
    int lo = 0;                         // not possible

    while (lo + 1 < hi) {
      int mid = (lo + (hi-lo)/2);

      if (possible(n, m, c, mid)) {
	hi = mid;
      } else {
	lo = mid;
      }
    }
    cout << hi << endl;
  }
  return 0;
}
