// just do it

#include <iostream>
#include <tr1/array>
#include <numeric>

using namespace std;
using namespace std::tr1;

array<int, 7> n;
array<int, 7> p;

bool read_n()
{
  for (array<int, 7>::iterator it = n.begin(); it != n.end(); ++it) {
    if (!(cin >> *it)) return false;
  }
  return true;
}

int main(void)
{
  while (read_n()) {
    int P;
    cin >> P;
    int N = accumulate(n.begin(), n.end(), 0);
    for (int i = 0; i < 7; i++) {
      p[i] = (P*n[i])/N;
    }
    int S = P - accumulate(p.begin(), p.end(), 0);
    for (int i = 0; i < 7 && S > 0; i++) {
      if (p[i] == 0) {
	p[i]++;
	S--;
      }
    }
    p[4] += S;

    for (int i = 0; i < 7; i++) {
      if (i) cout << ' ';
      cout << p[i];
    }
    cout << endl;
  }

  return 0;
}
