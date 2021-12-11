#include <bits/stdc++.h>

using namespace std;


int A[10][10];

typedef pair<int,int> pii;

int step()
{
  queue<pii> flash;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      A[i][j]++;
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (A[i][j] > 9) {
	flash.emplace(i,j);
      }
    }
  }

  while (!flash.empty()) {
    auto curr = flash.front();
    flash.pop();
    int i = curr.first, j = curr.second;
    for (int i2 = i-1; i2 <= i+1; i2++) {
      for (int j2 = j-1; j2 <= j+1; j2++) {
	if (i2 == i && j2 == j) continue;
	if (0 <= i2 && i2 < 10 && 0 <= j2 && j2 < 10 && A[i2][j2] < 10) {
	  A[i2][j2]++;
	  if (A[i2][j2] > 9) {
	    flash.emplace(i2, j2);
	  }
	}
      }
    }
  }

  int num_flashes = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (A[i][j] > 9) {
	num_flashes++;
	A[i][j] = 0;
      }
    }
  }

  return num_flashes;
}

void print()
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cout << A[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

int main()
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      char c;
      cin >> c;
      A[i][j] = c - '0';
    }
  }

  int ans = 0;
  for (int i = 0; i < 100; i++) {
    ans += step();
  }
  cout << ans << endl;
  
  return 0;
}
