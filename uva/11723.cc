#include <iostream>

using namespace std;

int main()
{
  int R, N;
  int id = 1;
  while (cin >> R >> N && (R || N)) {
    cout << "Case " << id++ << ": ";
    int s = (R + (N-1))/N - 1;
    if (s <= 26) {
      cout << s << endl;
    } else {
      cout << "impossible" << endl;
    }
  }

  return 0;
}
