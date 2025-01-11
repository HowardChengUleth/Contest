#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int N;
  cin >> N;

  vector<int> price(N);
  for (int i = 0; i < N; i++) {
    cin >> price[i];
  }

  int biggest = *max_element(begin(price), end(price));
  int smallest = *min_element(begin(price), end(price));

  int cost = smallest - biggest/2;
  if (cost < 0) {
    cost = 0;
  }

  cout << cost << endl;

  return 0;
}
