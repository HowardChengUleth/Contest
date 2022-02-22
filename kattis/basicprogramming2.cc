#include <bits/stdc++.h>

using namespace std;

int N, t;
int A[200000];

void solve1()
{
  // we don't have to worry about x = y because 7777 is odd
  for (int i = 0; i < N; i++) {
    if (binary_search(A, A+N, 7777-A[i])) {
      cout << "Yes" << endl;
      return;
    }
  }
  cout << "No" << endl;
}

void solve2()
{
  for (int i = 0; i < N-1; i++) {
    if (A[i] == A[i+1]) {
      cout << "Contains duplicate" << endl;
      return;
    }
  }
  cout << "Unique" << endl;
}

void solve3()
{
  map<int,int> freq;
  for (int i = 0; i < N; i++) {
    if (++freq[A[i]] > N/2) {
      cout << A[i] << endl;
      return;
    }
  }
  cout << -1 << endl;
}

void solve4()
{
  if (N % 2 == 1) {
    cout << A[N/2] << endl;
  } else {
    cout << A[N/2-1] << ' ' << A[N/2] << endl;
  }
}

void solve5()
{
  for (int i = 0; i < N; i++) {
    if (100 <= A[i] && A[i] <= 999) {
      cout << A[i] << ' ';
    }
  }
  cout << endl;
}

int main()
{
  cin >> N >> t;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  sort(A, A+N);

  switch (t) {
  case 1:
    solve1();
    break;
  case 2:
    solve2();
    break;
  case 3:
    solve3();
    break;
  case 4:
    solve4();
    break;
  case 5:
    solve5();
    break;
  }


  return 0;
}
