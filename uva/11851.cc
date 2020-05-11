#include <iostream>
#include <algorithm>
#include <list>
#include <climits>
#include <functional>

using namespace std;

bool negative_sum(const pair<int, int> &p)
{
  return p.first < 0;
}

void compute_list(int val[], int N, list< pair<int, int> > &sumlist)
{
  // we are going to do dynamic programming.
  //
  // For each value, we will try to give it to Jack, to Jill, or to no one.
  // We remember for each possible sum (both + and -) what is the maximum
  // amount property assigned.  We are going to maintain this information as
  // a sorted list of pairs (diff, total assigned).  The trick is to
  // traverse this list quickly and maintain it properly.

  list< pair<int, int> > table[2];
  int curr = 0;
  
  // for the first one we can just give it to Jack (or not give it at all)
  // insert fake one at the end to make things a little easier
  table[curr].push_back(make_pair(0, 0));
  table[curr].push_back(make_pair(INT_MAX, 0));

  list< pair<int, int> >::iterator itminus, itplus, it;

  for (int i = 0; i < N; i++) {
    int next = 1 - curr;
    table[next].clear();
    table[next] = table[curr];

    itminus = itplus = table[next].begin();
    for (it = table[curr].begin(); it != table[curr].end()
	   && it->first != INT_MAX; ++it) {
      int newval = it->first - val[i];
      int newtotal = it->second + val[i];
      while (newval > itminus->first)
	++itminus;
      if (newval == itminus->first)
	itminus->second = max(itminus->second, newtotal);
      else
	table[next].insert(itminus, make_pair(newval, newtotal));
      newval = it->first + val[i];
      while (newval > itplus->first)
	++itplus;
      if (newval == itplus->first)
	itplus->second = max(itplus->second, newtotal);
      else
 	table[next].insert(itplus, make_pair(newval, newtotal));
    }
    
    curr = next;

    /*
    for (it = table[curr].begin(); it != table[curr].end(); ++it) {
      cout << "(" << it->first << ", " << it->second << ") ";
    }
    cout << endl;
    */
    //    cout << "size = " << table[curr].size() << endl;
  }
  sumlist = table[curr];
  sumlist.remove_if(negative_sum);
}


bool do_case()
{
  int N;
  cin >> N;
  if (N == 0) return false;

  int val[24];
  int total = 0;
  for (int i = 0; i < N; i++) {
    cin >> val[i];
    total += val[i];
  }

  sort(val, val+N);
  
  list<pair<int, int> > first, second;
  
  compute_list(val, N/2, first);  
  compute_list(val+N/2, N-N/2, second);

  list<pair<int, int> >::iterator it1, it2;

  /*
  cout << "first = " << endl;
  for (it1 = first.begin(); it1 != first.end(); ++it1) {
    cout << "(" << it1->first << ", " << it1->second << ") ";
  }
  cout << endl;
  cout << "second = " << endl;
  for (it1 = second.begin(); it1 != second.end(); ++it1) {
    cout << "(" << it1->first << ", " << it1->second << ") ";
  }
  cout << endl;
  */
  it1 = first.begin();
  it2 = second.begin();
  int maxsum = 0;
  while (it1 != first.end() && it2 != second.end()) {
    if (it1->first == INT_MAX || it2->first == INT_MAX) break;
    if (it1->first == it2->first) {
      maxsum = max(maxsum, it1->second + it2->second);
      it1++;  it2++;
    } else if (it1->first < it2->first) {
      it1++;
    } else {
      it2++;
    }
  }

  cout << total - maxsum << endl;
  
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
