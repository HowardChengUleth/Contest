#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> subsets(ll A[], int n)
{
  vector<ll> v;
  v.reserve(1LL << n);
  for (int m = 1; m < (1LL << n); m++) {
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      if (m & (1LL << i)) {
	sum += A[i];
      }
    }
    v.push_back(sum);
  }

  sort(begin(v), end(v));
  return v;
}

// q(x) = number of subsets with sum <= x
ll q(ll x, const vector<ll> &v1, const vector<ll> &v2)
{
  ll ans = 0;

  ll i1 = 0, i2 = v2.size()-1;
  ll n1 = v1.size();
  
  while (n1 > 0 && v1[n1-1] > x) {
    n1--;
  }
  ans += n1;
  
  while (i2 >= 0 && v2[i2] > x) {
    i2--;
  }
  ans += i2+1;

  while (i1 < n1 && i2 >= 0) {
    ll sum = v1[i1] + v2[i2];
    if (sum > x) {
      i2--;
    } else {
      ans += i2+1;
      i1++;
    }
  }

  return ans;
}

int main()
{
  int N;
  cin >> N;

  ll A[42];
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  
  auto v1 = subsets(A, N/2);
  auto v2 = subsets(A+N/2, N - N/2);

  for (int i = 0; i < v1.size()-1; i++) {
    if (v1[i] == v1[i+1]) {
      cout << v1[i] << endl;
      return 0;
    }
  }

  for (int i = 0; i < v2.size()-1; i++) {
    if (v2[i] == v2[i+1]) {
      cout << v2[i] << endl;
      return 0;
    }
  }

  // [lo, hi]: there are at least hi-lo+2 subsets with sum in this range
  ll lo = 1, hi = (1LL << N)-2;
  while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;

    if (q(mid, v1, v2) - q(lo-1, v1, v2) >= mid - lo + 2) {
      hi = mid;
    } else {
      lo = mid+1;
    }
  }

  cout << lo << endl;

  return 0;
}
