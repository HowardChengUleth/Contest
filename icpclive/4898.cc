#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int min(int a, int b, int c)
{
  return min(min(a,b),c);
}

int edit_dist(string w1, string w2)
{
  int n1 = w1.length(), n2 = w2.length();

  int table[256][256];

  table[0][0] = 0;
  for (int j = 1; j <= n2; j++) {
    table[0][j] = j;
  }
  for (int i = 1; i <= n1; i++) {
    table[i][0] = i;
  }

  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      if (w1[i-1] == w2[j-1]) {
	table[i][j] = min(table[i-1][j-1], table[i-1][j]+1, table[i][j-1]+1);
      } else {
	table[i][j] = min(table[i-1][j-1], table[i-1][j], table[i][j-1]) + 1;
      }
    }
  }

  return table[n1][n2];
}

int main(void)
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    string word1, word2;
    cin >> word1 >> word2;
    cout << i << ". Edit Distance = " << edit_dist(word1, word2) << endl;
  }

  return 0;
}
