#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int X;
  cin >> X;
  for (int i = 1; i <= X; i++) {
    cout << "Case " << i << ": ";

    int R, C, M, N;
    cin >> R >> C >> M >> N;

    int freq[256] = {0};
    for (int i = 0; i < R*C; i++) {
      char ch;
      cin >> ch;
      freq[ch]++;
    }

    int hi = *max_element(freq, freq+256);
    int sum = 0;
    for (int i = 'A'; i <= 'Z'; i++) {
      sum += freq[i] * ((freq[i] == hi) ? M : N);
    }
    cout << sum << endl;
  }
  return 0;

}
