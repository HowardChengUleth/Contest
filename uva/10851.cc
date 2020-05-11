#include <string>
#include <iostream>

using namespace std;

int main(void)
{
  int N;
  cin >> N;
  cin.ignore(1);
  while (N--) {
    string grid[10];
    for (int i = 0; i < 10; i++) {
      cin >> grid[i];
    }
    int M = grid[0].length()-2;
    cin.ignore(1);

    for (int i = 1; i <= M; i++) {
      int c = 0;
      for (int j = 8; j >= 1; j--) {
	c <<= 1;
	c |= (grid[j][i] == '\\');
      }
      cout << (char)(c);
    }
    cout << endl;
  }
  return 0;
}
