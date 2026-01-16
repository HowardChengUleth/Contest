#include <bits/stdc++.h>

using namespace std;

int rank2score(int rank)
{
  const int table[] = {
    100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16,
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
  };

  if (rank < 30) {
    return table[rank];
  } else {
    return 0;
  }
}

struct Contestant
{
  int s, p, f, o;
  int score;
  int index;

  void read(int i)
  {
    index = i;
    cin >> s >> p >> f >> o;
    score = -1;
  }

  bool operator<(const Contestant &c) const
  {
    if (s != c.s) {
      return s < c.s;
    }
    if (p != c.p) {
      return p > c.p;
    }
    return f > c.f;
  }

  bool operator==(const Contestant &c) const
  {
    return s == c.s && p == c.p && f == c.f;
  }
};

vector<Contestant> A;

int main()
{
  int n;
  cin >> n;

  A.resize(n);
  for (int i = 0; i < n; i++) {
    A[i].read(i);
  }
  sort(rbegin(A), rend(A));

  for (int i = 0; i < n; i++) {
    if (A[i].score >= 0) continue;

    int sum = 0;
    int group = 0;
    for (int j = i; j < n && A[i] == A[j]; j++) {
      sum += rank2score(j);
      group++;
    }

    for (int j = i; j < n && A[i] == A[j]; j++) {
      A[j].score = (sum + (group-1))/group + A[j].o;
    }
  }
  
  vector<int> score(n);
  for (int i = 0; i < n; i++) {
    score[A[i].index] = A[i].score;
  }
  for (auto s : score) {
    cout << s << endl;
  }
  
  return 0;
}
