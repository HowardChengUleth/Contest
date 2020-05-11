// consider this as a nim game with 4 heaps, where each heap is the number
// of squares one can take away from each direction to get to the bad cake.
// Making all heaps 0 means that we have just one square with the bad cake.

#include <iostream>

using namespace std;

int main(void)
{
  int t;
  cin >> t;
  while (t-- > 0) {
    int m, n, r, c;
    cin >> m >> n >> r >> c;
    int sum = r ^ c ^ (m-1-r) ^ (n-1-c);
    if (sum) {
      cout << "Gretel" << endl;
    } else {
      cout << "Hansel" << endl;
    }
  }

  return 0;
}
