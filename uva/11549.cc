// Sonny's test solution to CCPC 2008, Problem C
// September 16, 2008

#include <iostream>
#include <set>

using namespace std;

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        int n;
        long long k;
        cin >> n >> k;

        // limit is highest number calculator can hold + 1
        long long limit = 1;
        for (int i = 0; i < n; ++i) limit *= 10;

        // just brute force repeatedly square until we hit a cycle
        set<long long> seen;
        while (seen.find(k) == seen.end())
        {
            seen.insert(k);
            k *= k;
            while (k >= limit) k /= 10;
        }

        set<long long>::iterator largest = --seen.end();
        cout << *largest << endl;
    }

    return 0;
}