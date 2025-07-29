#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<string> phrase;
    string word;

    while (cin >> word) {
	phrase.push_back(word);
    }

    sort(begin(phrase), end(phrase));
    for (int i = 1; i < phrase.size(); i++) {
	if (phrase[i-1] == phrase[i]) {
	    cout << "no" << endl;
	    return 0;
	}
    }

    cout << "yes" << endl;
    

    return 0;
}
