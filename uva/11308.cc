#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

char upper(char c)
{
  return toupper((int)c);
}

int main(void)
{
  int c;
  cin >> c;
  cin.ignore(1);

  while (c-- > 0) {
    string title;
    getline(cin, title);
    transform(title.begin(), title.end(), title.begin(), upper);
    cout << title << endl;
    
    int m, n, b;
    cin >> m >> n >> b;

    string ing_name[100];
    int ing_cost[100];
    for (int i = 0; i < m; i++) {
      cin >> ing_name[i] >> ing_cost[i];
      cin.ignore(1);
    }
    
    vector< pair<int, string> > recipe;
    for (int i = 0; i < n; i++) {
      string rep_name;
      getline(cin, rep_name);
      
      int k;
      cin >> k;

      int cost = 0;

      for (int j = 0; j < k; j++) {
	string ing;
	int units;
	cin >> ing >> units;
	cin.ignore(1);
	int index = find(ing_name, ing_name+m, ing) - ing_name;
	cost += units * ing_cost[index];
      }

      if (cost <= b) {
	recipe.push_back(make_pair(cost, rep_name));
      }
    }

    sort(recipe.begin(), recipe.end());
    if (recipe.size() > 0) {
      for (unsigned int i = 0; i < recipe.size(); i++) {
	cout << recipe[i].second << endl;
      }
    } else {
      cout << "Too expensive!" << endl;
    }

    cout << endl;
  }
  return 0;
}
