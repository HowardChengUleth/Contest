#include <bits/stdc++.h>

using namespace std;

struct Line
{
  int start_r, start_c;
  int dr, dc;

  void horiz(int r)
  {
    start_r = r;
    start_c = 0;
    dr = 0;
    dc = 1;
  }

  void vert(int c)
  {
    start_r = 0;
    start_c = c;
    dr = 1;
    dc = 0;
  }

  void diag1(int n)
  {
    start_r = start_c = 0;
    dr = 1;
    dc = 1;
  }

  void diag2(int n)
  {
    start_r = 0;
    start_c = n-1;
    dr = 1;
    dc = -1;
  }

};

int N;
string A[8];
Line line[20];
int num_lines = 0;

typedef unsigned long long ll;

ll count_grid(ll mask)
{
  bool used[8][8] = {false};
  for (int i = 0; i < num_lines; i++) {
    if (!(mask & (1ULL << i))) continue;
    int r = line[i].start_r, c = line[i].start_c;
    for (int j = 0; j < N; j++) {
      if (A[r][c] == 'O') {
	// not possible
	return 0;
      }
      used[r][c] = true;
      r += line[i].dr;
      c += line[i].dc;
    }
  }

  int count = 0;
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      if (!used[r][c] && A[r][c] == '.') {
	count++;
      }
    }
  }

  return (1ULL << count);
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  for (int i = 0; i < N; i++) {
    line[num_lines++].horiz(i);
    line[num_lines++].vert(i);
  }
  line[num_lines++].diag1(N);
  line[num_lines++].diag2(N);

  ll ans = 0;
  for (ll mask = 1; mask < (1ULL << num_lines); mask++) {
    int sign = (__builtin_popcount(mask) % 2 == 1) ? 1 : -1;
    ans += sign * count_grid(mask);
  }
  cout << ans << endl;
  
  return 0;
}
