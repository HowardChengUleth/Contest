#include <iostream>

using namespace std;

void do_case()
{
  int N, B, X, Y;
  int n = 0;
  int mult = 1;

  cin >> N >> B >> X >> Y;
  while (X > 0 || Y > 0) {
    int dx = X % B;
    int dy = Y % B;

    X /= B;
    Y /= B;
    n += (dx + dy) % B * mult;
    mult *= B;
  }

  cout << N << ' ' << n << endl;

}

int main(void)
{
  int P;
  cin >> P;
  while (P--) {
    do_case();
  }
  return 0;
}
