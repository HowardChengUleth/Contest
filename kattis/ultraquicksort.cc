#include <bits/stdc++.h>

using namespace std;

int64_t merge(vector<int> &v, int s, int m, int e)
{
  vector<int> temp(e - s);

  int64_t ans = 0;
  
  int i1 = s, i2 = m;
  int ti = 0;
  while (i1 < m && i2 < e) {
    if (v[i1] <= v[i2]) {
      temp[ti++] = v[i1++];
    } else {
      temp[ti++] = v[i2++];
      ans += m - i1;
    }
  }

  // only one of the two is non-empty
  copy(begin(v) + i1, begin(v) + m, begin(temp) + ti);
  copy(begin(v) + i2, begin(v) + e, begin(temp) + ti);

  copy(begin(temp), end(temp), begin(v) + s);

  return ans;
}

int64_t inversions(vector<int> &v, int start, int end)
{
  if (end - start <= 1) {
    return 0;
  }

  int mid = start + (end - start)/2;

  int64_t ans = inversions(v, start, mid) + inversions(v, mid, end);
  ans += merge(v, start, mid, end);

  return ans;
}


int main()
{
  int n;
  cin >> n;

  vector<int> v(n);
  for (auto &x : v) {
    cin >> x;
  }

  cout << inversions(v, 0, n) << endl;

  return 0;
}
