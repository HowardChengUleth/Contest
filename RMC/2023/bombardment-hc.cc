#include <bits/stdc++.h>

using namespace std;

typedef int ll;
int N;
ll R;
vector<ll> ans;

void do_pass(vector<ll> &x)
{
  int best_s = 0, best_count = -1;
  ll best_hit = -R;
  
  int e = 0;
  for (int s = 0; s < x.size(); s++) {
    for ( ; e < x.size() && x[e] <= x[s] + 2*R; e++)
      ;
    int num_hit = e - s;
    if (num_hit > best_count) {
      best_count = num_hit;
      best_s = s;
      assert(e >= 1);
      best_hit = x[e-1] - R;
    }
  }

  ans.push_back(best_hit);

  int dest = best_s;
  for (int i = best_s; i < x.size(); i++) {
    if (x[i] <= best_hit + R) continue;
    x[dest++] = x[i];
  }

  x.resize(dest);
}

int main()
{
  cin >> N >> R;
  
  vector<ll> x(N);
  for (auto &val : x) {
    cin >> val;
  }
  sort(begin(x), end(x));

  while (x.size() > 0) {
    do_pass(x);
  }

  cout << ans.size() << endl;
  for (auto val : ans) {
    cout << val << ' ';
  }
  cout << endl;
  return 0;
}
