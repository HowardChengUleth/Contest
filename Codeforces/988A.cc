#include <bits/stdc++.h>

using namespace std;

// Idea is to count the number of unique ratings.  Since the ratings are
// in the range 1-100, we just have to remember the index of each rating
// if it occurs (if there are multiple, any will do).

int main()
{
  int n, k;
  cin >> n >> k;

  int index[101] = {0};
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    index[a] = i+1;
  }

  int unique = 100 - count(index+1, index+101, 0);
  if (unique < k) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
    for (int i = 1; i <= 100 && k > 0; i++) {
      if (!index[i]) continue;
      cout << index[i] << ' ';
      k--;
    }
    cout << endl;
  }
  return 0;
}
