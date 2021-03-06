#include <cstdlib>
#include <vector>
#include <cstdio>
#include <cctype>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const int mod = 1e9 + 7;
//Module_Group
//usage: MG<long long prim_>
template<long long m> struct MG {
	typedef long long LL;
	LL x;
	//constructor
	//usage: MG(long long vaule)
	MG(LL _x = 0): x(_x % m) {
	}
	friend MG operator + (MG p, MG q) {
		return (p.x + q.x) % m;
	}
	friend MG operator - (MG p, MG q) {
		return MG((p.x - q.x + m) % m);
	}
	friend MG operator * (MG p, MG q) {
		return MG((p.x * q.x) % m);
	}
	friend MG operator / (MG p, MG q) {
		MG a(1);
		LL b = m - 2;
		for (; b; b >>= 1) {
			if (b & 1) {
				a = a * q;
			}
			q = q * q;
		}
		return p * a;
	}
};
typedef MG<mod> Int;
int n, m, g[maxn];
Int fac[maxn], pow[maxn];
int main()
{
#if 1
	freopen("input.txt", "r", stdin);
#endif
	fac[0] = pow[0] = 1;
	for (int i = 1; i < 1010; i++) {
		fac[i] = fac[i - 1] * i;
		pow[i] = pow[i - 1] * 2;
	}
#if 0
	printf("fac: ");
	for (int i = 0; i < 11; i++) {
		printf(" %d", fac[i]);
	}
	puts("");
	printf("pow: ");
	for (int i = 0; i < 11; i++) {
		printf(" %d", pow[i]);
	}
	puts("");
#endif
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < m; i++) {
			scanf("%d", g + i);
		}
		sort(g, g + m);
		Int res = fac[n - m], div = 1;
		g[m++] = n + 1;
		for (int i = 0; i < m; i++) {
			int rem = g[i] - (i? g[i - 1]: 0) - 1;
			if (0 < i && i < m - 1) {
				res = res * pow[max(0, rem - 1)];
			}
			div = div * fac[rem];
#if 0
			printf("%lld, %lld\n", pow[max(0, rem - 1)], fac[rem]);
#endif
		}
		printf("%lld\n", res / div);
	}
	return 0;
}
