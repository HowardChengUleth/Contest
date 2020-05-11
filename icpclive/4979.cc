#include <iostream>
#include <string>

using namespace std;

string board[5];

bool check(char x)
{
  int dr[4] = { 0, 1, 1, 1};
  int dc[4] = { 1, 0, 1, -1 };
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      for (int dir = 0; dir < 4; dir++) {
	int count = 0;
	for (int k = 0; k < 3; k++) {
	  int newr = r + k*dr[dir];
	  int newc = c + k*dc[dir];
	  if (!(0 <= newr && newr < 5 && 0 <= newc && newc < 5)) break;
	  if (board[newr][newc] == x) {
	    count++;
	  }
	}
	if (count == 3) {
	  return true;
	}
      }
    }
  }
  return false;
}

int main(void)
{
  int Z;
  cin >> Z;
  while (Z--) {
    for (int i = 0; i < 5; i++) {
      cin >> board[i];
    }

    bool Awin = check('A');
    bool Bwin = check('B');
    if (Awin == Bwin) {
      cout << "draw" << endl;
    } else {
      cout << (Awin ? "A wins" : "B wins") << endl;
    }
  }
  return 0;
}
