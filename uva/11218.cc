#include <iostream>

using namespace std;

int main(void)
{
  int n;
  int cases = 0;

  while (cin >> n && n > 0) {
    cases++;

    int best = -1;
    int score[81], mask[81];
    for (int i = 0; i < n; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      cin >> score[i];
      mask[i] = (1 << a) | (1 << b) | (1 << c);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	if (mask[i] & mask[j]) continue;
	for (int k = 0; k < n; k++) {
	  if ((mask[i] & mask[k]) || (mask[j] & mask[k])) continue;
	  int temp = score[i] + score[j] + score[k];
	  if (temp > best) {
	    best = temp;
	  }
	}
      }
    }
    cout << "Case " << cases << ": " << best << endl;
  }
  return 0;
}
