#include <iostream>
#include <algorithm>

using namespace std;

bool solve()
{
  int N;
  if (!(cin >> N)) return false;

  int zero[26], one[26];
  bool special[26];

  for (int i = 0; i < N; i++) {
    char name, z, o, s;
    cin >> name >> z >> o >> s;
    zero[name-'A'] = z - 'A';
    one[name-'A'] = o - 'A';
    special[name-'A'] = (s == 'x');
  }

  int ways[31][26];
  for (int i = 0; i < N; i++) {
    ways[0][i] = (special[i]) ? 1 : 0;
  }
  
  int m;
  cin >> m;

  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < N; j++) {
      ways[i][j] = ways[i-1][zero[j]] + ways[i-1][one[j]];
    }
  }

  cout << ways[m][0] << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
