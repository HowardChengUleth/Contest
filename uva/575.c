/* @JUDGE_ID: 1102NT 575 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

unsigned long convert(char *s)
{
    int n, i;
    unsigned long res = 0;
    unsigned long b;

    n = strlen(s);
    for (i = 0; i < n; i++) {
	b = (0x01 << (i+1)) - 1;
	res += (s[n-1-i] - '0')*b;
    }
    return res;
}

int main(void)
{
    char buffer[100];
    unsigned long res;
    int i;

    scanf("%s", buffer);
    res = convert(buffer);
    while (res) {
	printf("%lu\n", res);
	scanf("%s", buffer);
	res = convert(buffer);
    }

    return 0;
}
