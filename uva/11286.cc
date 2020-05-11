#include <iostream>
#include <tr1/tuple>
#include <map>
#include <algorithm>

using namespace std;
using namespace std::tr1;

typedef tuple<int,int,int,int,int> T;

int main(void)
{
  int n;
  while (cin >> n && n) {
    map<T, int> count;

    int best = 0;
    T t;
    for (int i = 0; i < n; i++) {
      int A[5];
      for (int j = 0; j < 5; j++) {
	cin >> A[j];
      }
      sort(A, A+5);
      get<0>(t) = A[0];
      get<1>(t) = A[1];
      get<2>(t) = A[2];
      get<3>(t) = A[3];
      get<4>(t) = A[4];
      best = max(best, ++count[t]);
    }

    int ans = 0;
    for (map<T, int>::const_iterator it = count.begin(); it != count.end();
	 ++it) {
      if (it->second == best) {
	ans += it->second;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
