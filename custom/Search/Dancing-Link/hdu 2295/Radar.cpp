#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;
//STL-Alias
#define UN(c, a) unique(c, a)
#define MS(c, a) memset(c, a, sizeof c)
#define FLC(c, a ,b) fill(c, c + a, b)
#define LOS(c, a, b) lower_bound(c, a, b)
#define UPS(c, a, b) upper_bound(c, a, b)
//Syntax-Alias
#define Rep(c, a, b) for (int c = (a); c < (b); c++)
#define Nre(c, a, b) for (int c = (a); c > (b); c--)
//DEBUG
#define FK puts("Fu*k here!")
#define PA(s, c, a, b, p, f){\
	printf(s);\
	Rep(c, a, b) printf(p, (f));\
	puts("");}
//Constant
#define EPS (1e-7)
#define MAXN (55)
#define INFI (0x7fffffff)
//Type-Alias
typedef long long LL;
typedef long double LD;
typedef int AI[MAXN];
typedef bool AB[MAXN];
typedef double AD[MAXN];
typedef LL ALL[MAXN];
typedef LD ALD[MAXN];

//DLX
struct DLX
{
#define DF(c, a, b) for (int c = a[b]; c != b; c = a[c])
	typedef int DI[MAXN * MAXN];
	DI L, R, U, D, C;
	AI S;
	int id, cr, rh, ms;
	void ini(int n)
	{
		id = ++n;
		Rep(i, 0, n)
		{
			L[i] = (i - 1 + n) % n;
			R[i] = (i + 1) % n;
			U[i] = D[i] = i;
		}
		MS(S, cr = 0);
		ms = INFI;
	}	
	void ins(int i, int j)
	{
		if (cr < i)
		{
			rh = L[id] = R[id] = id;
			cr = i;
		}
		L[id] = L[rh]; R[id] = rh;
		R[L[rh]] = id; L[rh] = id;
		U[id] = U[j]; D[id] = j;
		D[U[j]] = id; U[j] = id;
		S[j]++; C[id++] = j;
	}
	void rrm(int c)
	{
		DF(i, D, c) L[R[i]] = L[i], R[L[i]] = R[i];
	}
	void rrs(int c)
	{
		DF(i, D, c) L[R[i]] = i, R[L[i]] = i;
	}
	int hfu()
	{
		int h = 0;
		AB H = {0};
		DF(c, R, 0) if (!H[c])
		{
			H[c] = 1;
			h++;
			DF(i, D, c) DF(j, R, i) H[C[j]] = 1;
		}
		return h;
	}
	bool rdf(int sp)
	{
		if (sp + hfu() >= ms) return 0;
		if (!R[0])
		{
			ms = min(ms, sp);
			return 1;
		}
		int x = R[0];
		DF(i, R, 0) if (S[i] < S[x]) x = i;
		DF(i, D, x)
		{
			rrm(i);
			DF(j, R, i) rrm(j);
			if (rdf(sp + 1)) return 1;
			DF(j, L, i) rrs(j);
			rrs(i);
		}
		return 0;
	}
	int rec()
	{
		ms = hfu();
		while (!rdf(0)) ms++;
		return ms;
	}
} dlx;

struct Vec
{
	double x, y;
	Vec(double _x = 0.0, double _y = 0.0): x(_x), y(_y) {} 
	void inp()
	{
		scanf("%lf%lf", &x, &y);
	}
	friend Vec operator - (Vec p, Vec q)
	{
		return Vec(p.x - q.x, p.y - q.y);
	}
	double mod()
	{
		return sqrt(x * x + y * y);
	}
} _vec, C[MAXN], R[MAXN];

int N, M, K;

int chk(double m)
{
	int ct = N;
	AB H = {0};
	dlx.ini(N);
	Rep(i, 0, M) Rep(j, 0, N)
		if ((R[i] - C[j]).mod() - m <= EPS)
		{
			if (!H[j])
			{
				H[j] = 1;
				ct--;
			}
			dlx.ins(i + 1, j + 1);
		}
	if (ct) return INFI;
	return dlx.rec(); 
}

int main()
{
#if 1
	freopen("test.txt", "r", stdin);
#endif
	int T, Cas = 1;
	scanf("%d", &T);
	while (T--)
	{
		//Initialize
		scanf("%d%d%d", &N, &M, &K);
		Rep(i, 0, N) C[i].inp();
		Rep(i, 0, M) R[i].inp();
		double l = 0, r = 2000.0, res = -1;
		//Solve
		while (l  - r <= EPS)
		{
			double m = (l + r) / 2.0;
			if (chk(m) <= K)
			{
				res = m;
				r = m - EPS;
			}
			else l = m + EPS;
		}
		printf("%.6lf\n", res);
	}
	return 0;
}
