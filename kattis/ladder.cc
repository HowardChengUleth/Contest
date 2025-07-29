#include <bits/stdc++.h>

using namespace std;

int main()
{
    double h, v;
    cin >> h >> v;

    const double PI = acos(-1.0);
    v *= PI/180.0;
    
    double len = ceil(h / sin(v));

    cout << setprecision(0) << fixed << len << endl;

    return 0;
}
