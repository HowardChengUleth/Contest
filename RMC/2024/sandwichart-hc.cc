#include <bits/stdc++.h>

using namespace std;

int N, G, D, M;

const int MAX_N = 1'000'000;
bool present[MAX_N];
vector<vector<int>> genre;
vector<int> depend[MAX_N];

queue<int> Q;

bool check_genre(int g)
{
  int count = 0;
  for (auto x : genre[g]) {
    count += present[x];
  }
  
  return count == N;
}

int main()
{
  cin >> N >> G >> D >> M;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    present[x] = true;
    Q.push(x);
  }

  genre.resize(G);
  for (int i = 0; i < G; i++) {
    int K;
    cin >> K;
    genre[i].resize(K);
    for (auto &x : genre[i]) {
      cin >> x;
    }
  }

  for (int i = 0; i < D; i++) {
    int I, J;
    cin >> I >> J;
    depend[I].push_back(J);
  }

  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();
    for (auto next : depend[curr]) {
      if (!present[next]) {
	present[next] = true;
	Q.push(next);
	N++;
      }
    }
  }

  bool bad = true;
  if (N <= M) {
    for (int i = 0; i < G && bad; i++) {
      if (check_genre(i)) {
	bad = false;
      }
    }
  }

  cout << (bad ? "disaster" : "masterpiece") << endl;
  
  return 0;
}
