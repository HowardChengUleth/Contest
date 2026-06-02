#include <bits/stdc++.h>

using namespace std;

typedef pair<int64_t,int64_t> pii;

// return (a,b): a = number of subsets of first N items of w that have >= min_w
//               b = total weights of such sets   
pii f(const int w[], int N, int min_w)
{
  if (min_w <= 0) {
    // we can take all possible subsets (including empty set), and
    // each element will appear in half the subsets and not in the other half
    //
    // this works even if N == 0
    int64_t num = 1ULL << N;
    int64_t total = accumulate(w, w+N, 0) * (num/2);
    return pii(num, total);
  } else if (N == 0) {
    // there are no sets that work
    return pii(0, 0);
  }

  // either we choose w[N-1] or not
  pii ans1 = f(w, N-1, min_w);
  pii ans2 = f(w, N-1, min_w - w[N-1]);
  ans2.second += w[N-1] * ans2.first;

  pii ans(ans1.first + ans2.first, ans1.second + ans2.second);
  
  return ans;
}

int main()
{
  int N;
  cin >> N;

  int w[40];
  for (int i = 0; i < N; i++) {
    cin >> w[i];
  }

  cout << f(w, N, 200).second << endl;

  return 0;
}
