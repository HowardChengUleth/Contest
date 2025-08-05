#include <bits/stdc++.h>

using namespace std;

int main()
{
    string A, B;
    cin >> A >> B;

    reverse(begin(A), end(A));
    reverse(begin(B), end(B));

    int a = stoi(A), b = stoi(B);

    cout << max(a, b) << endl;

    return 0;
}
