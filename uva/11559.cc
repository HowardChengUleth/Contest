#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int N, B, H, W;
  while (cin >> N >> B >> H >> W) {
    int best = B+1;
    
    while (H--) {
      int cost;
      cin >> cost;
      for (int i = 0; i < W; i++) {
	int cap;
	cin >> cap;
	if (cap < N) continue;
	best = min(best, N*cost);
      }
    }

    if (best <= B) {
      cout << best << endl;
    } else {
      cout << "stay home" << endl;
    }
  }

  return 0;
}
