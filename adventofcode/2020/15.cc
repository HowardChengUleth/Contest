#include <bits/stdc++.h>

using namespace std;


const int N = 30000000;

int seq[N] = {0, 14, 6, 20, 1, 4};
int n = 6;

/*
int seq[N] = {0,3,6};
int n = 3;
*/

int main()
{

  unordered_map<int, pair<int,int>> last;
  unordered_map<int,int> seen;
  for (int i = 0; i < n; i++) {
    auto &p = last[seq[i]];
    p.second = p.first;
    p.first = i;
    seen[seq[i]]++;
  }

  for (int i = n; i < N; i++) {
    int curr;
    if (seen[seq[i-1]] == 1) {
      curr = 0;
    } else {
      auto p = last[seq[i-1]];
      curr = p.first - p.second;
    }
    
    auto &p = last[curr];
    p.second = p.first;
    p.first = i;
    seq[i] = curr;
    seen[curr]++;
  }

  cout << "A = " << seq[2019] << endl;
  cout << "B = " << seq[N-1] << endl;

  return 0;
}
