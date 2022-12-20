#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll key = 811589153;
vector<pii> A;
vector<int> pos;

void mix(int i)
{
  // element to move
  int t = pos[i];
  auto val = A[t].second;

  if (!val) return;
  
  int dir, inc;
  if (val > 0) {
    val %= A.size() - 1;
    dir = -1;
    inc = 1;
  } else if (val < 0) {
    val = -(-val % (A.size() - 1));
    dir = 1;
    inc = A.size()-1;
  }

  while (val) {
    int next = (t + inc) % A.size();
    swap(A[t], A[next]);
    pos[A[t].first] = t;
    pos[A[next].first] = next;
    t = next;
    val += dir;
  }
}

int main()
{
  ll x;
  int index = 0;
  while (cin >> x) {
    A.emplace_back(index++, x * key);
  }
  int n = A.size();
  pos.resize(n);
  for (int i = 0; i < n; i++) {
    pos[i] = i;
  }

  for (int R = 0; R < 10; R++) {
    for (int i = 0; i < n; i++) {
      mix(i);
    }
  }

  int pos0 = 0;
  for (int i = 0; i < n; i++) {
    if (A[i].second == 0) {
      pos0 = i;
      break;
    }
  }
  auto v1 = A[(pos0 + 1000) % n].second;
  auto v2 = A[(pos0 + 2000) % n].second;
  auto v3 = A[(pos0 + 3000) % n].second;

  cout << v1 << ' ' << v2 << ' ' << v3 << endl;
  cout << v1+v2+v3 << endl;
  
  return 0;
}
