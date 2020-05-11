#include <iostream>
#include <queue>

using namespace std;

void solve(void)
{
  int A[30000], u[30000];
  int n, m;

  cin >> m >> n;
  for (int i = 0; i < m; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> u[i];
  }

  // queues containing those <= and >= i-th element, so that
  // there are always i+1 element in le.
  priority_queue<int> le, ge;
  int ai = 0;

  le.push(A[ai++]);
  for (int ui = 0; ui < n; ui++) {
    while (le.size() + ge.size() < u[ui]) {
      if (le.top() <= A[ai]) {
	ge.push(-A[ai]);
      } else {
	int t = le.top();
	le.pop();
	le.push(A[ai]);
	ge.push(-t);
      }
      ai++;
    }
    cout << le.top() << endl;
    if (ge.size() > 0) {
      int t = ge.top();
      ge.pop();
      le.push(-t);
    } else {
      le.push(A[ai++]);
    }
  }
}

int main(void)
{
  int K;

  cin >> K;

  for (int i = 1; i <= K; i++) {
    if (i > 1) {
      cout << endl;
    }
    solve();
  }
  return 0;
}
