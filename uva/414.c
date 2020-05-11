/* @JUDGE_ID: 1102NT 414 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void)
{
    char buffer[1024];
    int n, i, j, count, min_count, k;

    while (scanf("%d", &n) == 1 && n > 0) {
	scanf("\n");
	count = 0;
	min_count = 25;
	for (i = 0; i < n; i++) {
	    fgets(buffer, 1024, stdin);
	    k = 0;
	    for (j = 0; j < 25; j++) {
		if (buffer[j] == ' ') {
		    count++;
		    k++;
		} else {
		    assert(buffer[j] == 'X');
		}
	    }
	    if (k < min_count) {
		min_count = k;
	    }
	}
	printf("%d\n", count - n*min_count);
    }
    return 0;
}
