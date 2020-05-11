#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int score(const string &s)
{
  int n = s.length();
  if (n < 3) return 0;
  if (n == 3 || n == 4) return 1;
  if (n == 5) return 2;
  if (n == 6) return 3;
  if (n == 7) return 5;
  return 11;
}
	  
string grid[4];

const int di[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dj[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool appears(const string &s, int i, int j)
{
  if (s.length() == 0) return true;
  if (!(0 <= i && i < 4 && 0 <= j && j < 4)) return false;
  if (grid[i][j] != s[0]) return false;

  grid[i][j] = ' ';
  for (int d = 0; d < 8; d++) {
    if (appears(s.substr(1), i+di[d], j+dj[d])) {
      grid[i][j] = s[0];
      return true;
    }
  }

  grid[i][j] = s[0];
  return false;
}

bool appears(const string &s)
{
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (appears(s, i, j)) {
	return true;
      }
    }
  }
  return false;
}

int score()
{
  for (int i = 0; i < 4; i++) {
    cin >> grid[i];
  }

  int M;
  cin >> M;
  string dict[100];
  for (int i = 0; i < M; i++) {
    cin >> dict[i];
  }

  int total = 0;
  for (int i = 0; i < M; i++) {
    if (appears(dict[i])) {
      total += score(dict[i]);
    }
  }
  
  return total;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Score for Boggle game #" << i << ": " << score() << endl;
  }
  return 0;
}
