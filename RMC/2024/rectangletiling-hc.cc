#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_EXP = 51;

pair<bool,ll> solve(ll W, ll H, ll A[])
{
  if (H > W) {
    return solve(H, W, A);
  }
  if (H == 0) {
    return make_pair(true, 0);
  }

  int largest = -1;
  for (int i = MAX_EXP-1; i >= 0; i--) {
    if (A[i] && (1LL << i) <= H) {
      largest = i;
      break;
    }
  }

  if (largest < 0) {
    return make_pair(false, 0);
  }

  // try to lay as many of them as we can, one column at a time
  ll blk_size = (1LL << largest);
  ll rows = H / blk_size;
  ll cols = W / blk_size;

  pair<bool,ll> res;
  
  // number of full cols, number of blocks in last col
  ll fill_cols = A[largest] / rows;
  ll last_col = A[largest] % rows;

  // we can fill everything
  if (fill_cols >= cols) {
    res = make_pair(true, rows * cols);
    A[largest] -= rows * cols;
    auto res2 = solve(H % blk_size, cols * blk_size, A);
    auto res3 = solve(H, W % blk_size, A);
    res.first &= (res2.first && res3.first);
    res.second += (res2.second + res3.second);
    return res;
  }

  // can't fill it all
  res = make_pair(true, A[largest]);
  A[largest] = 0;

  ll W1 = fill_cols * blk_size;
  if (last_col > 0) {
    W1 += blk_size;
  }
  
  auto res2 = solve(H % blk_size, W1, A);
  auto res3 = solve(H, W-W1, A);
  res.first &= (res2.first && res3.first);
  res.second += (res2.second + res3.second);

  if (last_col > 0) {
    auto res4 = solve((rows - last_col) * blk_size, blk_size, A);
    res.first &= res4.first;
    res.second += res4.second;
  }
  
  return res;

}

int main()
{
  ll W, H, N;
  ll A[MAX_EXP] = { 0 };
  
  cin >> W >> H >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  auto res = solve(W, H, A);
  if (res.first) {
    cout << res.second << endl;
  } else {
    cout << -1 << endl;
  }
  
  return 0;
}
