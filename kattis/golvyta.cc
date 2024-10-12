#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> parse(string s, char plus, char minus)
{
  vector<int> v;
  v.reserve(s.length());
  for (auto ch : s) {
    if (ch == plus) {
      v.push_back(1);
    } else if (ch == minus) {
      v.push_back(-1);
    }
  }
  return v;
}

int simulate(const vector<int> &v, int limit)
{
  int curr = 0;
  for (auto s : v) {
    curr += s;
    curr = min(limit-1, curr);
    curr = max(0, curr);
  }
  return curr;
}

int solve(const vector<int> &v, int target)
{
  int lo = 1, hi = v.size()+1;

  if (target == 0) {
    return 1;
  }
  
  if (simulate(v, hi) < target) {
    return -1;
  }
  
  // lo = < target, hi >= target
  while (hi - lo > 1) {
    int mid = lo + (hi - lo) / 2;
    int end = simulate(v, mid);
    if (end >= target) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  if (simulate(v, hi) == target) {
    return hi;
  }

  return -1;
}

int main()
{
  int K;
  string s;
  int r, c;

  cin >> K >> s >> r >> c;

  auto vert = parse(s, 'v', '^');
  auto horiz = parse(s, '>', '<');

  ll N = solve(vert, r);
  ll M = solve(horiz, c);

  if (N == -1 || M == -1) {
    cout << -1 << endl;
  } else {
    cout << N * M << endl;
  }
  

  return 0;
}
