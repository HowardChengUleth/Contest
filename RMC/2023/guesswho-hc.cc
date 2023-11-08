#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000;
const int MAX_M = 15;

int main()
{
  int N, M, Q;
  cin >> N >> M >> Q;

  string attrib[MAX_N];
  for (int i = 0; i < N; i++) {
    cin >> attrib[i];
  }

  string query(MAX_M, ' ');
  for (int i = 0; i < Q; i++) {
    int A;
    char resp;
    cin >> A >> resp;
    query[A-1] = resp;
  }

  int count = 0;
  int hidden = -1;
  for (int i = 0; i < N; i++) {
    bool match = true;
    for (int j = 0; j < M; j++) {
      match &= (query[j] == ' ' || query[j] == attrib[i][j]);
    }
    if (match) {
      count++;
      hidden = i+1;
    }
  }

  if (count == 1) {
    cout << "unique" << endl;
    cout << hidden << endl;
  } else {
    cout << "ambiguous" << endl;
    cout << count << endl;
  }
  
  return 0;
}
