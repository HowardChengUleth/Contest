#include <iostream>
#include <algorithm>
#include <iomanip>
#include <utility>

using namespace std;

int main(void)
{
  int region = 1;
  int m, n;
  while (cin >> m >> n && (m || n)) {
    cout << "Region " << region++ << endl;

    int levels[900];
    for (int i = 0; i < m*n; i++) {
      cin >> levels[i];
    }
    sort(levels, levels+m*n);

    int total = 0;
    double height = levels[0];
    int under = 0;
    cin >> total;
    for (int i = 1; i < m*n && total > 0; i++) {
      int diff = levels[i] - levels[i-1];
      int area = i*100;
      int used = min(area * diff, total);
      total -= used;
      height += (double)used/area;
      under = i;
    }

    if (total > 0) {
      height += (double)total/(m*n*100);
      under = m*n;
    }
    cout << "Water level is " << fixed << setprecision(2) << height
	 << " meters." << endl;
    cout << (double)under*100.0/(m*n)
	 << " percent of the region is under water." << endl;
    cout << endl;
  }
  return 0;
}
