#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <string.h>
#include <iostream>
using namespace std;
const int maxn = 1e3 + 10;
int a[maxn];
int main()
{
#if 0
	freopen("input.txt", "r", stdin);
#endif
	int n;
	while (~scanf("%d", &n)) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < n; i++) {
			int ai;
			scanf("%d", &ai);
			a[ai]++;
		}
		bool yes = 1;
		for (int i = 0; i < maxn; i++) {
			if (n + 1 < 2 * a[i]) {
				yes = 0;
				break;
			}
		}
		puts(yes? "YES": "NO");
	}
	return 0;
}
