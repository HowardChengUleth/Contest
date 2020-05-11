#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int,int> Coord;
typedef pair<Coord,int> Elem;

int main(void)
{
  int m, n;
  while (cin >> m >> n) {
    Elem A[1000];
    int num = 0;
    
    for (int i = 1; i <= m; i++) {
      int r;
      cin >> r;
      int col[1000];
      for (int j = 0; j < r; j++) {
	cin >> col[j];
      }
      for (int j = 0; j < r; j++) {
	int val;
	cin >> val;
	A[num++] = make_pair(make_pair(col[j], i), val);
      }
    }

    sort(A, A+num);
    cout << n << ' ' << m << endl;
    int k = 0;
    for (int row = 1; row <= n; row++) {
      if (k >= num || row < A[k].first.first) {
	cout << "0" << endl << endl;
	continue;
      }

      int count;
      for (count = 0; k+count < num &&
	     A[k+count].first.first == A[k].first.first; count++)
	;
      cout << count;
      for (int i = 0; i < count; i++) {
	cout << ' ' << A[k+i].first.second;
      }
      cout << endl;
      for (int i = 0; i < count; i++) {
	if (i) cout << ' ';
	cout << A[k+i].second;
      }
      cout << endl;
      k += count;
    }
  }

  return 0;
}
