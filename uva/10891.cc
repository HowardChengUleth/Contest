#include <iostream>
#include <numeric>

using namespace std;

int A[100];
int partial[100];
int best[100][100];
bool init[100][100];

int range_sum(int s, int e)
{
  return partial[e] - (s > 0 ? partial[s-1] : 0);
}

int f(int s, int e)
{
  if (init[s][e]) {
    return best[s][e];
  }

  if (s == e) {
    init[s][e] = true;
    return best[s][e] = A[s];
  }

  init[s][e] = true;
  best[s][e] = range_sum(s, e);

  for (int c = s; c < e; c++) {
    int left = range_sum(s, c) - f(c+1, e);
    int right = range_sum(c+1, e) - f(s, c);
    best[s][e] = max(best[s][e], max(left, right));
  }

  return best[s][e];
}

int main(void)
{
  int n;
  while (cin >> n && n) {
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    partial_sum(A, A+n, partial);
    
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	init[i][j] = false;
      }
    }
    
    cout << f(0, n-1) << endl;
  }
  return 0;
}
