#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  int earliest = -1, latest = 1001;
  
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    earliest = max(a, earliest);
    latest = min(b, latest);
  }

  if (earliest <= latest) {
    cout << "gunilla has a point" << endl;
  } else {
    cout << "edward is right" << endl;
  }

  return 0;
}
