/* @JUDGE_ID: 1102NT 294 C "Sieve" */
#include <stdio.h>
#include <stdlib.h>

int d[10001];

int do_case(int l, int u)
{
    int i, k, start, best, best_i;

    for (i = 0; i < u-l+1; i++) {
	d[i] = 0;
    }
    for (k = 1; k*k <= u; k++) {
	start = (l % k == 0) ? 0 : k - (l % k);
	for (i = start; i < u-l+1; i += k) {
	    if (k*k == l+i) {
		d[i]++;
	    } else if (k*k < l+i) {
		d[i] += 2;
	    }
	}
    }

    best = 0;
    for (i = 0; i < u-l+1; i++) {
	if (d[i] > best) {
	    best_i = i;
	    best = d[i];
	}
    }
    return best_i + l;

}

void main(void)
{
    int n, u, l, p;

    scanf("%d", &n);
    while (n-- > 0) {
	scanf("%d %d", &l, &u);
	p = do_case(l, u);
	printf("Between %d and %d, %d has a maximum of %d divisors.\n", 
	       l, u, p, d[p-l]);
    }
}
