#include <iostream>
#include <string>

using namespace std;

void solve()
{
  int N;
  string A[100];
  int index = -1;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    if (A[i][0] != '#') {
      index = i;
    }
  }

  bool printed = false;
  for (int i = index+1; i < N; i++) {
    if (printed) cout << ' ';
    cout << A[i];
    printed = true;
  }
  if (index >= 0) {
    if (printed) cout << ' ';
    cout << A[index];
    printed = true;
  }
  for (int i = 0; i < index; i++) {
    if (printed) cout << ' ';
    cout << A[i];
    printed = true;
  }
  cout << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
