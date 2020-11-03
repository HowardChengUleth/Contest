#include <bits/stdc++.h>

using namespace std;

int main()
{
  double A, N;
  cin >> A >> N;

  const double PI = acos(-1.0);
  double r = sqrt(A / PI);
  double circ = 2 * PI * r;

  if (circ <= N) {
    cout << "Diablo is happy!" << endl;
  } else {
    cout << "Need more materials!" << endl;
  }

  return 0;
}
