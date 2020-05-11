#include <iostream>

using namespace std;

void closure(bool A[26][26])
{
  for (int k = 0; k < 26; k++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
	A[i][j] |= A[i][k] && A[k][j];
      }
    }
  }
}

void solve()
{
  int N1, N2;
  bool A1[26][26], A2[26][26];

  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      A1[i][j] = A2[i][j] = false;
    }
  }

  cin >> N1;
  for (int i = 0; i < N1; i++) {
    char a, b;
    cin >> a >> b;
    A1[a-'A'][b-'A'] = true;
  }
  cin >> N2;
  for (int i = 0; i < N2; i++) {
    char a, b;
    cin >> a >> b;
    A2[a-'A'][b-'A'] = true;
  }
  
  closure(A1);
  closure(A2);
  bool good = true;
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      good &= ((A1[i][j] && A2[i][j]) || (!A1[i][j] && !A2[i][j]));
    }
  }
  if (good) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    solve();
    if (N) {
      cout << endl;
    }
  }

  return 0;
}
