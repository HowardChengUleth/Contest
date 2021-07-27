#include <bits/stdc++.h>

using namespace std;

void rotate(char G[10][10], int n)
{
  char T[10][10];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      T[i][j] = G[n-1-j][i];
    }
  }
  for (int i = 0; i < n; i++) {
    copy(T[i], T[i]+n, G[i]);
  }
  
}

int main()
{
  int n;
  char G[10][10];
  
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> G[i][j];
    }
  }

  string s;
  cin >> s;

  char D[10][10] = {0};
  int k = 0;
  for (int t = 0; t < 4; t++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	if (G[i][j] == 'X') continue;
	if (k >= n*n || D[i][j]) goto bad;
	D[i][j] = s[k++];
      }
    }

    rotate(G, n);
  }

  if (k != n*n) goto bad;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << D[i][j];
    }
  }
  cout << endl;
    
  return 0;

 bad:
  cout << "invalid grille" << endl;
  return 0;
}
