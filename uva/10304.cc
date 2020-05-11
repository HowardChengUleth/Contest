#include <iostream>
#include <numeric>

using namespace std;

int n;
int f[250];
int table[250][250];
int fsum[250][250];

int compute(int start, int end)
{
  if (start > end) {
    return 0;
  }
  if (table[start][end] >= 0) {
    return table[start][end];
  }

  if (start == end) {
    return table[start][end] = 0;
  }

  for (int mid = start; mid <= end; mid++) {
    int temp = 0;
    if (start < mid) {
      temp += fsum[start][mid-1] + compute(start, mid-1);
    }
    if (mid < end) {
      temp += fsum[mid+1][end] + compute(mid+1, end);
    }

    if (table[start][end] < 0 || temp < table[start][end]) {
      table[start][end] = temp;
    }
  }

  return table[start][end];
}

bool solve()
{
  if (!(cin >> n)) return false;

  for (int i = 0; i < n; i++) {
    cin >> f[i];
  }

  for (int i = 0; i < n; i++) {
    fsum[i][i] = f[i];
    for (int j = i+1; j < n; j++) {
      fsum[i][j] = fsum[i][j-1] + f[j];
    }
  }

  
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      table[i][j] = -1;
    }
  }
  cout << compute(0, n-1) << endl;
  
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
