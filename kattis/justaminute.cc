#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  int Msum = 0, Ssum = 0;
  for (int i = 0; i < N; i++) {
    int M, S;
    cin >> M >> S;
    Msum += M;
    Ssum += S;
  }

  Msum *= 60;
  if (Ssum <= Msum) {
    cout << "measurement error" << endl;
  } else {
    cout << fixed << setprecision(10) << double(Ssum)/Msum << endl;
  }
  
  return 0;
}
