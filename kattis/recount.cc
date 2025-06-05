#include <bits/stdc++.h>

using namespace std;

int main()
{
    map<string,int> freq;

    int total = 0;
    string name;
    int max_vote = 0;
    while (getline(cin, name) && name != "***") {
	max_vote = max(max_vote, ++freq[name]);
	total++;
    }

    string winner;
    for (auto [n, f] : freq) {
	if (f == max_vote) {
	    if (winner == "") {
		winner = n;
	    } else {
		cout << "Runoff!" << endl;
		return 0;
	    }
	}
    }

    cout << winner << endl;

    return 0;
}
