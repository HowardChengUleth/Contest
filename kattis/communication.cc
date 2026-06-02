#include <bits/stdc++.h>

using namespace std;

int encode(int x)
{
  return x ^ ((x << 1) & 0xFF);
}

int table[256];

void init()
{
  for (int i = 0; i < 256; i++) {
    table[encode(i)] = i;
  }
}

int main()
{
  init();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    if (i) {
      cout << ' ';
    }
    
    int b;
    cin >> b;
    cout << table[b];
  }
  cout << endl;
  
  return 0;
}
