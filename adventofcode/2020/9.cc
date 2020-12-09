#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
vector<ll> A;

const int window = 25;

int main()
{
  ll x;
  while (cin >> x) {
    A.push_back(x);
  }

  ll targetB;
  for (int i = window; i < A.size(); i++) {
    ll target = A[i];
    bool good = false;
    for (int j = 0; j < window && !good; j++) {
      for (int k = j+1; k < window && !good; k++) {
	if (A[i-1-j] != A[i-1-k] && A[i-1-j] + A[i-1-k] == target) {
	  good = true;
	}
      }
    }
    if (!good) {
      cout << "A = " << target << endl;
      targetB = target;
      break;
    }
  }

  int s = 0, e = 0;
  ll sum = 0;
  while (s < A.size() && e < A.size()) {
    if (sum < targetB) {
      sum += A[e++];
    } else if (sum > targetB) {
      sum -= A[s++];
    } else if (sum == targetB) {
      ll small = *min_element(begin(A)+s, begin(A)+e);
      ll big = *max_element(begin(A)+s, begin(A)+e);
      cout << "B = " << small + big << endl;
      break;
    }
  }
  
  return 0;
}
