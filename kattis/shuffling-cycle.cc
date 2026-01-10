#include <bits/stdc++.h>

using namespace std;

void shuffle(int deck[], int N, const string &dir)
{
  int deck2[1000];

  int p1, p2;
  
  if (dir == "out") {
    p1 = 0;
    p2 = (N+1)/2;
  } else {
    p1 = N/2;
    p2 = 0;
  }
  
  int to = 0;

  for (int i = 0; i < N/2; i++) {
    deck2[to++] = deck[p1++];
    deck2[to++] = deck[p2++];
  }
  if (N % 2) {
    deck2[to++] = deck[p1++];
  }
  
  copy(deck2, deck2+N, deck);
}

int find_cycle(const int deck[], int N,
	       int cycle_len[],
	       int start)
{
  if (cycle_len[start] == -1) {
    return 0;
  }

  int to = deck[start];
  cycle_len[start] = -1;
  return find_cycle(deck, N, cycle_len, to) + 1;
}

int gcd(int a, int b)
{
  if (b == 0) {
    return a;
  }
  return gcd(b, a%b);
}

int lcm(const int A[], int N)
{
  int ans = A[0];
  for (int i = 1; i < N; i++) {
    ans = ans * (A[i]/gcd(ans, A[i]));
  }
  return ans;
}

void print_deck(const int deck[], int N)
{
  for (int i = 0; i < N; i++) {
    cout << deck[i] << ' ';
  }
  cout << endl;
}

int main()
{
  int N;
  string dir;

  cin >> N >> dir;

  int deck[1000];
  iota(deck, deck+N, 0);

  shuffle(deck, N, dir);

  int cycle_len[1000];
  fill(cycle_len, cycle_len+N, 0);

  for (int i = 0; i < N; i++) {
    if (cycle_len[i] == 0) {
      int len = find_cycle(deck, N, cycle_len, i);
      replace(cycle_len, cycle_len+N, -1, len);
    }
  }

  cout << lcm(cycle_len, N) << endl;
  
  return 0;
}
