#include <iostream>

using namespace std;

int main(void)
{
  int K;

  while (cin >> K && K > 0) {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < K; i++) {
      int X, Y;
      cin >> X >> Y;
      if (N == X || M == Y) {
	cout << "divisa" << endl;
      } else {
	cout << (Y > M ? 'N' : 'S')
	     << (X > N ? 'E' : 'O') << endl;
      }
    }

  }
  
  return 0;
}
