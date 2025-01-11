#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;
  if (N % 2) {
    cout << "still running" << endl;
    return 0;
  }


  int total = 0;
  for (int i = 0; i < N; i += 2) {
    int start, end;
    cin >> start >> end;
    total += end - start;
  }
  cout << total << endl;

  return 0;
}
