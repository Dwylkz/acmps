//Kimady::S.X.Dwylkz
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
//Namespace
namespace dtd{
	//Constant
	const long long INFLL = ~0uLL>>1;
	const int INFI = ~0u>>1;
	const int MAXN = 10e5+10;
	const int MAXM = 100;
	const int MOD = 1e9+7;
	//Type Definition
	typedef unsigned int UI;
	typedef long long LL;
	typedef long double LD;
	typedef int AI[MAXN];
	typedef bool AB[MAXN];
	typedef double AD[MAXN];
	typedef LL ALL[MAXN];
	typedef LD ALD[MAXN];
	typedef AI AI2[MAXM];
	typedef AB AB2[MAXM];
	typedef AD AD2[MAXM];
	typedef ALL ALL2[MAXM];
	typedef ALD ALD2[MAXM];
}
using namespace std;
using namespace dtd;
//Macro
#define Bug puts("Here")
//Global
int n;
ALL s, p, l;
//Main
int main()
{
#if 0
	freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
#endif
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%lld", s + i);
		}
		for (int i = 0; i < n; i++) {
			scanf("%lld", p + i);
		}
		sort(s, s + n);
		sort(p, p + n);
		int j = 0;
		s[n] = INFI;
		for (int i = 0; i < n + 1; i++) {
			while (j < n && p[j] < s[i]) {
				l[j++] = i;
			}
		}
		while (j < n) {
			l[j] = l[j - 1];
			j++;
		}
		LL ans = 1;
		for (int i = 0; i < n; i++) {
			ans = ans * (l[i] - i) % MOD;
		}
#if 0
		for (int i = 0; i < n; i++) {
			printf("%5d", s[i]);
		}
		puts("");
		for (int i = 0; i < n; i++) {
			printf("%5d", p[i]);
		}
		puts("");
		for (int i = 0; i < n; i++) {
			printf("%5d", l[i]);
		}
		puts("");
#endif
		printf("%lld\n", ans);
	}
	return 0;
}
