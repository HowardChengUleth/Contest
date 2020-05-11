#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

int main()
{
  priority_queue< pair<int, int> > pq;
  int period[3001];
  
  string cmd;
  while (cin >> cmd && cmd != "#") {
    int ID, t;
    cin >> ID >> t;
    period[ID] = t;
    pq.push(make_pair(-t, -ID));
  }

  int K;
  cin >> K;
  for (int i = 0; i < K; i++) {
    pair<int,int> data = pq.top();
    pq.pop();
    cout << -data.second << endl;
    data.first -= period[-data.second];
    pq.push(data);
  }
  
  return 0;
}
