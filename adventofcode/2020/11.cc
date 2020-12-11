#include <bits/stdc++.h>

using namespace std;

vector<string> stepA(const vector<string> &A)
{
  int M = A.size(), N = A[0].size();
  vector<string> ans = A;

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (A[r][c] == '.') continue;
      int occ = 0;
      for (int i = -1; i <= 1; i++) {
	for (int j = -1; j <= 1; j++) {
	  if (!i && !j) continue;
	  if (0 <= r+i && r+i < M && 0 <= c+j && c+j < N) {
	    if (A[r+i][c+j] == '#') {
	      occ++;
	    }
	  }
	}
      }
      if (A[r][c] == 'L' && occ == 0) {
	ans[r][c] = '#';
      }
      if (A[r][c] == '#' && occ >= 4) {
	ans[r][c] = 'L';
      }
    }
  }
  return ans;
}

vector<string> stepB(const vector<string> &A)
{
  const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  
  int M = A.size(), N = A[0].size();
  vector<string> ans = A;

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (A[r][c] == '.') continue;
      int occ = 0;

      for (int d = 0; d < 8; d++) {
	for (int r2 = r+dr[d], c2 = c+dc[d];
	     0 <= r2 && r2 < M && 0 <= c2 && c2 < N;
	     r2 += dr[d], c2 += dc[d]) {
	  if (A[r2][c2] == '#') {
	    occ++;
	    break;
	  } else if (A[r2][c2] == 'L') {
	    break;
	  }
	}
      }

      if (A[r][c] == 'L' && occ == 0) {
	ans[r][c] = '#';
      }
      if (A[r][c] == '#' && occ >= 5) {
	ans[r][c] = 'L';
      }
    }
  }
  return ans;
}

int main()
{
  vector<string> origA;
  string s;
  while (getline(cin, s)) {
    origA.push_back(s);
  }
  
  vector<string> A = origA, A2;

  do {
    A2.swap(A);
    A = stepA(A2);
  } while (A != A2);

  int ansA = 0;
  for (auto s : A) {
    for (auto c : s) {
      if (c == '#') {
	ansA++;
      }
    }
  }
  cout << "A = " << ansA << endl;

  A = origA;
  do {
    A2.swap(A);
    A = stepB(A2);
  } while (A != A2);
  
  int ansB = 0;
  for (auto s : A) {
    for (auto c : s) {
      if (c == '#') {
	ansB++;
      }
    }
  }
  cout << "B = " << ansB << endl;

  return 0;
}
