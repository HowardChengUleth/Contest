#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

struct Piece
{
  int id;
  bool A[3][3];

  void read()
  {
    char colon;
    cin >> id >> colon;

    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
	char ch;
	cin >> ch;
	A[r][c] = (ch == '#');
      }
    }
  }

  int area() const
  {
    int ans = 0;
    for (int r = 0; r < 3; r++) {
      ans += count(A[r], A[r]+3, true);
    }
    return ans;
  }
  
  void flip()
  {
    for (int r = 0; r < 3; r++) {
      swap(A[r][0], A[r][2]);
    }
  }

  void rotate()
  {
    int B[3][3];

    for (int r = 0; r < 3; r++) {
      copy(A[r], A[r]+3, B[r]);
    }

    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
	A[r][c] = B[c][2-r];
      }
    }
  }
};

Piece piece[6];

bool canfit(int freq[6])
{
  int area = 0;
  for (int i = 0; i < 6; i++) {
    area += piece[i].area() * freq[i];
  }

  if (area > M*N) {
    return false;
  } else {
    int blocks = M/3 * N/3;
    int total_freq = accumulate(freq, freq+6, 0);
      
    cout << "excess = " << M*N - area << endl;
    cout << "blocks - total_freq = " << blocks - total_freq << endl;
    assert(blocks >= total_freq);
  }


  return true;
}

int main()
{
  for (int i = 0; i < 6; i++) {
    piece[i].read();
  }

  int total = 0;
  
  char ch;
  while (cin >> M >> ch >> N >> ch) {
    int freq[6];
    for (int i = 0; i < 6; i++) {
      cin >> freq[i];
    }

    total += canfit(freq);
  }

  cout << total << endl;
  return 0;
}
