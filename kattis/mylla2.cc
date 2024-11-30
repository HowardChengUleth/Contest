#include <iostream>

using namespace std;

bool checkline(bool A[3][3], int start_r, int start_c, int dr, int dc)
{
  for (int i = 0; i < 3; i++) {
    if (!A[start_r][start_c]) {
      return false;
    }
    start_r += dr;
    start_c += dc;
  }
  return true;
}

int main()
{
  bool A[3][3];
  const int sr[8] = { 0, 1, 2, 0, 0, 0, 0, 0 };
  const int sc[8] = { 0, 0, 0, 0, 1, 2, 0, 2 };
  const int dr[8] = { 0, 0, 0, 1, 1, 1, 1, 1 };
  const int dc[8] = { 1, 1, 1, 0, 0, 0, 1, -1 };

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      char ch;
      cin >> ch;
      A[r][c] = (ch == 'O');
    }
  }

  bool win = false;

  for (int i = 0; i < 8; i++) {
    win |= checkline(A, sr[i], sc[i], dr[i], dc[i]);
  }

  if (win) {
    cout << "Jebb" << endl;
  } else {
    cout << "Neibb" << endl;
  }
  
  return 0;
}
