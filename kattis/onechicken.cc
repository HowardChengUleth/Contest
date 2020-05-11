#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;

  if (M >= N) {
    int left = M-N;
    cout << "Dr. Chaz will have " << left << (left == 1 ? " piece" : " pieces")
	 << " of chicken left over!" << endl;
  } else {
    int need = N-M;
    cout << "Dr. Chaz needs " << need << " more " << (need == 1 ? " piece" : " pieces")
	 << " of chicken!" << endl;
  }

  return 0;
}
