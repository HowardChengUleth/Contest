/* @JUDGE_ID: 1102NT 417 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *strings[90000];
int num;

int valid(char *buffer)
{
    int i, n;

    n = strlen(buffer);
    for (i = 0; i < n-1; i++) {
	if (buffer[i] >= buffer[i+1]) {
	    return 0;
	}
    }
    return 1;
}

int cmp(char *s1, char *s2)
{
    int n1, n2;

    n1 = strlen(s1);
    n2 = strlen(s2);
    if (n1 != n2) {
	return n1 - n2;
    }
    return strcmp(s1, s2);
}

int windex(char *buffer)
{
    int t, l, r, m;

    l = 0;
    r = num;
    m = (l+r)/2;
    while ((t = cmp(buffer, strings[m])) && l < r) {
	if (t < 0) {
	    r = m;
	} else if (t > 0) {
	    l = m+1;
	}
	m = (l+r)/2;
    }
    assert(l < r);
    return m+1;
}

void build_table(void)
{
    int k, i1, i2, i3, i4, i5;
    char buffer[1024];

    for (i1 = 0; i1 < 90000; i1++) {
	strings[i1] = malloc(6*sizeof(char));
    }

    k = 0;
    
    for (i1 = 0; i1 < 26; i1++) {
	buffer[0] = i1 + 'a';
	buffer[1] = 0;
	strcpy(strings[k++], buffer);
    }

    for (i1 = 0; i1 < 26; i1++) {
	buffer[0] = i1 + 'a';
	for (i2 = i1+1; i2 < 26; i2++) {
	    buffer[1] = i2 + 'a';
	    buffer[2] = 0;
	    strcpy(strings[k++], buffer);
	}
    }

    for (i1 = 0; i1 < 26; i1++) {
	buffer[0] = i1 + 'a';
	for (i2 = i1+1; i2 < 26; i2++) {
	    buffer[1] = i2 + 'a';
	    for (i3 = i2+1; i3 < 26; i3++) {
		buffer[2] = i3+'a';
		buffer[3] = 0;
		strcpy(strings[k++], buffer);
	    }
	}
    }

    for (i1 = 0; i1 < 26; i1++) {
	buffer[0] = i1 + 'a';
	for (i2 = i1+1; i2 < 26; i2++) {
	    buffer[1] = i2 + 'a';
	    for (i3 = i2+1; i3 < 26; i3++) {
		buffer[2] = i3+'a';
		for (i4 = i3+1; i4 < 26; i4++) {
		    buffer[3] = i4 + 'a';
		    buffer[4] = 0;
		    strcpy(strings[k++], buffer);
		}
	    }
	}
    }

    for (i1 = 0; i1 < 26; i1++) {
	buffer[0] = i1 + 'a';
	for (i2 = i1+1; i2 < 26; i2++) {
	    buffer[1] = i2 + 'a';
	    for (i3 = i2+1; i3 < 26; i3++) {
		buffer[2] = i3+'a';
		for (i4 = i3+1; i4 < 26; i4++) {
		    buffer[3] = i4 + 'a';
		    for (i5 = i4+1; i5 < 26; i5++) {
			buffer[4] = i5 + 'a';
			buffer[5] = 0;
			strcpy(strings[k++], buffer);
		    }
		}
	    }
	}
    }

    num = k;
}



int main(void)
{
    char buffer[1024];
    int i;

    build_table();

    while (scanf("%s", buffer) == 1) {
	if (valid(buffer)) {
	    printf("%d\n", windex(buffer));
	} else {
	    printf("0\n");
	}
    }
    return 0;
}
