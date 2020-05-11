#include <iostream>
#include <algorithm>
#include <map>
#include <tr1/tuple>

using namespace std;
using namespace std::tr1;

typedef tuple<int,int,int> tiii;
map<tiii, long long> ans;

long long solve(int K, int A, int B)
{
  if (K == 0) return 1;

  if (ans.find(tiii(K, A, B)) != ans.end()) {
    return ans[tiii(K, A, B)];
  }
  
  int half = 1 << (K-1);

  if (B < half) {
    return ans[tiii(K, A, B)] = 2*solve(K-1, A, B);
  }
  if (A >= half) {
    return ans[tiii(K, A, B)] = solve(K-1, A-half, B-half);
  }

  return ans[tiii(K, A, B)] = 2*solve(K-1, A, half-1) + solve(K-1, 0, B-half);
}

int main()
{
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int K, A, B;
    cin >> K >> A >> B;
    cout << "Case " << i+1 << ": " << solve(K, A-1, B-1) << endl;
  }
  return 0;
}
