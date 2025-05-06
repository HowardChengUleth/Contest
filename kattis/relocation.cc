#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, Q;
  cin >> N >> Q;

  int pos[100001];
  for (int i = 1; i <= N; i++) {
    cin >> pos[i];
  }

  for (int i = 0; i < Q; i++) {
    int cmd;
    cin >> cmd;
    if (cmd == 1) {
      int C, X;
      cin >> C >> X;
      pos[C] = X;
    } else {
      int A, B;
      cin >> A >> B;
      cout << abs(pos[A] - pos[B]) << endl;
    }
  }

  return 0;
}
