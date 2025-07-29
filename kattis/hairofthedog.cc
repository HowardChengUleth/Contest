#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;

    int hungover = 0;
    string prev = "sober";
    
    for (int i = 0; i < N; i++) {
	string state;
	cin >> state;

	if (prev == "drunk" && state != "drunk") {
	    hungover++;
	}

	prev = state;
    }

    cout << hungover << endl;
    
    return 0;
}
