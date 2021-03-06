//coder: SXDwylkz
//heads
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
//namespaces
using namespace std;
//constants
const char input[] = "input.in",
	  output[] = "output.out";
const int inf32 = 0x7fffffff,
	  maxn = 55,
	  maxm = 11;
const long long inf64 = 0x7fffffffffffffffLL; 
//structure
//AC Automaton
//include: queue, cstring
//usage: obj.Init->obj.Link->(obj.$(others))*->obj.Free
struct ACA {
	enum {n = 11, m = 55, shift = 0};
	struct Node {
		//Extern
		//Basic
		Node *s[m],             //Adjust node
			 *p;                //Failure link
		int  a;                 //Accpet Tag
	};
	typedef Node *PNode;
	//Extern
	//Basic
	int sz;
	Node t[110];
	PNode   rt;                   //Initial State
	//Init a node
	//usage: obj.New([length], [Failure Link])
	PNode New() {
		memset(t + sz, 0, sizeof(Node));
		return t + sz++;
	}
	//Init
	//usage: obj.Init()
	void Init() {
		//Extern
		//Basic
		sz = 0;
		rt = New();
	}
	//Append a string
	//usage: obj.Insert(charactor)
	void Insert(int a, int *s, int sl) {
		PNode x = rt;
		for (int i = 0; i < sl; i++) {
			int k = s[i] - shift;
			if (!x->s[k]) {
				x->s[k] = New();
			}
			x = x->s[k];
		}
		x->a = a;
	}
	//Failure Linking
	//usage: obj.Link()
	void Link() {
		queue<PNode> Q;
		rt->p = rt;
		for (int i = 0; i < m; i++) {
			if (rt->s[i]) {
				rt->s[i]->p = rt;
				Q.push(rt->s[i]);
			} else {
				rt->s[i] = rt;
			}
		}
		while (!Q.empty()) {
			PNode x = Q.front();
			Q.pop();
			for (int i = 0; i < m; i++) {
				if (x->s[i]) {
					x->s[i]->p = x->p->s[i];
					if (x->p->s[i]->a) {
						x->s[i]->a = x->p->s[i]->a;
					}
					Q.push(x->s[i]);
				} else {
					x->s[i] = x->p->s[i];
				}
			}
		}
	}
};
struct HT {
	enum {sz = 256};
	int h[sz], index;
	void Init() {
		index = 0;
		memset(h, -1, sizeof(h));
	}
	int operator [] (int x) {
		if (h[x] == -1) {
			h[x] = index++;
		}
		return h[x];
	}
};
struct Int {
	enum {sz = 90};
	int s[sz];
	Int(const char *x = "0") {
		memset(s, 0, sizeof(s));
		for (int xl = s[0] = strlen(x), i = xl; 0 < i; i--) {
			s[i] = x[xl - i] - '0';
		}
	}
	friend Int operator + (Int p, Int q) {
		Int o;
		o[0] = max(p[0], q[0]);
		for (int i = 1; i <= o[0]; i++) {
			o[i] += p[i] + q[i];
			o[i + 1] = o[i] / 10;
			o[i] %= 10;
		}
		if (o[o[0] + 1]) {
			o[0]++;
		}
		return o;
	}
	int & operator [] (int x) {
		return s[x];
	}
	void Print() {
		for (int i = s[0]; 0 < i; i--) {
			printf("%d", s[i]);
		}
	}
};
//type definition
typedef long long LL;
//global variable
HT ht;
ACA aca;
int N, M, P, buf[maxn];
unsigned char a[maxn], p[maxn];
Int dp[maxn][110];
//access and mutator
bool YYCIO() {
#if 0
	for (int i = 0; i < aca.sz; i++) {
		printf("%d\n", aca.t[i].a);
	}
	puts("");
#endif
	for (int i = 0; i < N; i++) {
		if (!aca.rt->s[i]->a) {
			return 0;
		}
	}
	return 1;
}
//main
int main() {
#if 1
	freopen(input, "r", stdin);
	//freopen(output, "w", stdout);
#endif
#if 0
	printf("Big number test:\n");
	Int A("1234567890"), B("0987654321");
	A.Print();
	printf("+\n");
	B.Print();
	printf("=\n");
	(A + B).Print();
	puts("");
#endif
	while (~scanf("%d%d%d", &N, &M, &P)) {
		ht.Init();
		scanf("%s", a);
		for (int i = 0; i < N; i++) {
			ht[a[0]];
		}
		aca.Init();
		for (int i = 0; i < P; i++) {
			scanf("%s", p);
			for (unsigned char *j = p; *j; j++) {
				buf[j - p] = ht[*j];
			}
			aca.Insert(strlen((char*)p), buf, strlen((char*)p));
		}
		aca.Link();
		for (int i = 0; i <= M; i++) {
			for (int j = 0; j < aca.sz; j++) {
				dp[i][j] = Int("0");
			}
		}
		dp[0][0] = Int("1");
		for (int i = 1; i <= M; i++) {
			for (int j = 0; j < aca.sz; j++) {
				for (int k = 0; k < N; k++) {
					int id = aca.t[j].s[k] - aca.t;
					if (!aca.t[id].a) {
						dp[i][id] = dp[i][id] + dp[i - 1][j];
					}
				}
			}
		}
		Int res;
		for (int i = 0; i < aca.sz; i++) {
			if (!aca.t[i].a) {
				res = res + dp[M][i];
			}
		}
		res.Print();
		puts("");
	}
	return 0;
}
