#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  string card;
  vector<Node> child;

  Node(const string &c) : card(c) { }
};

void add(vector<Node> &list, const vector<string> &hand, int size, int index)
{
  int i;
  
  if (index >= size) return;
  
  for (i = 0; i < list.size(); i++) 
    if (list[i].card == hand[index]) 
      break;

  if (i == list.size()) {
    list.push_back(Node(hand[index]));
  }
  
  add(list[i].child, hand, size, index+1);
}

int count(const vector<Node> &list)
{
  int n = list.size();
  int total = n;

  for (int i = 0; i < n; i++) {
    total += count(list[i].child);
  }
  return total;

}

int main(void)
{
  int hands;

  while (cin >> hands && hands) {
    vector<Node> child;

    while (hands-- > 0) {
      int cards;
      cin >> cards;
      vector<string> v(cards);
      while (cards-- > 0) {
	cin >> v[cards];
      }

      add(child, v, v.size(), 0);
    }

    cout << count(child) << endl;

  }

  return 0;
}
