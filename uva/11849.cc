#include <iostream>

using namespace std;

int main(void)
{
  int A1[1000000], A2[1000000];
  int N, M;
  while (cin >> N >> M && (N || M)) {
    int count1 = 0, count2 = 0;
    for (int i = 0; i < N; i++) {
      cin >> A1[count1];
      if (count1 == 0 || A1[count1] != A1[count1-1]) {
	count1++;
      }
    }
    for (int i = 0; i < M; i++) {
      cin >> A2[count2];
      if (count2 == 0 || A2[count2] != A2[count2-1]) {
	count2++;
      }
    }
    int i1 = 0, i2 = 0;
    int ans = 0;
    while (i1 < count1 && i2 < count2) {
      if (A1[i1] == A2[i2]) {
	ans++;
	i1++;
	i2++;
      } else if (A1[i1] < A2[i2]) {
	i1++;
      } else {
	i2++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
