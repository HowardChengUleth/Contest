#include <iostream>

using namespace std;

int main()
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cout << "Case " << i << ": ";

    int h, m, t1, t2, t3, t4;
    char dummy;
    cin >> h >> dummy >> m;
    t1 = h*60+m;
    cin >> h >> dummy >> m;
    t2 = h*60+m;
    cin >> h >> dummy >> m;
    t3 = h*60+m;
    cin >> h >> dummy >> m;
    t4 = h*60+m;

    if (t2 < t3 || t4 < t1) {
      cout << "Hits Meeting" << endl;
    } else {
      cout << "Mrs Meeting" << endl;
    }
  }
  
  return 0;
}
