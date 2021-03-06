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
	  maxn = 1e5 + 10;
const long long inf64 = 0x7fffffffffffffffLL; 
//structure
//AC Automaton
//include: queue, cstring
//usage: obj.Init->obj.Link->(obj.$(others))*->obj.Free
struct ACA {
	const static int m = 256,  //Size of charator set
		  shift = 0;           //Charactor shift
	struct Node {
		//Extern
		//Basic
		Node *s[m],             //Adjust node
			 *p;                //Failure link
		int  a;                 //Accpet state or not
	};
	typedef Node *PNode;
	//Extern
	//Basic
	stack<PNode> ct;
	PNode   rt;                   //Initial State
	//Init a node
	//usage: obj.New([length], [Failure Link])
	PNode New() {
		PNode x = (PNode)malloc(sizeof(Node));
		memset(x, 0, sizeof(Node));
		ct.push(x);
		return x;
	}
	//Init
	//usage: obj.Init()
	void Init() {
		//Extern
		//Basic
		for ( ; !ct.empty(); ct.pop()) {
		}
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
		x->a++;
	}
	//Failure Linking
	//usage: obj.Link()
	void Link() {
		queue<PNode> Q;
		for (Q.push(rt); !Q.empty(); ) {
			PNode x = Q.front();
			Q.pop();
			for (int i = 0; i < m; i++) {
				if (x->s[i]) {
					if (x == rt) {
						x->s[i]->p = x;
					} else {
						PNode y = x->p;
						for (; y && !y->s[i]; y = y->p) {
						}
						if (!y) {
							x->s[i]->p = rt;
						} else {
							x->s[i]->p = y->s[i];
						}
					}
					Q.push(x->s[i]);
				}
			}
		}
	}
	//statistic work
	//usage: obj.Search(key array, array length)
	int Search(int *s, int sl) {
		int total = 0;
		PNode x = rt;
		map<PNode, bool> h;
		h.clear();
		for (int i = 0; i < sl; i++) {
			int k = s[i] - shift;
			for ( ; x && (k < 0 ||  m <= k || !x->s[k]); x = x->p) {
			}	
			if (!x) {
				x = rt;
				continue;
			}
			for (PNode y = x->s[k]; y; y = y->p) {
				if (h.find(y) == h.end()) {
					total += y->a;
					h[y] = 1;
				}
			}
			x = x->s[k];
		}
		return total;
	}
	//Free spaces
	//usage: obj.Free()
	void Free(PNode x = 0) {
		for ( ; !ct.empty(); ct.pop()) {
			free(ct.top());
		}
	}
};
//type definition
typedef long long LL;
//global variable
ACA aca;
int n, m;
char ask[maxn], key[maxn], dc[256];
//access and mutator
void dc_Init() {
	for (int i = 0; i < 26; i++) {
		dc['A' + i] = i;
		dc['a' + i] = 26 + i;
	}
	for (int i = 0; i < 10; i++) {
		dc['0' + i] = 52 + i;
	}
	dc['+'] = 62;
	dc['/'] = 63;
}
int decode(int *s, int sl) {
	static int t[maxn];
	int tl = 0;
	for (int i = 0; i < sl; i += 4, tl += 3) {
		int *in = s + i, *out = t + tl;
		out[0] = (dc[in[0]] << 2) | (dc[in[1]] >> 4);
		out[1] = in[2] == '='? 0x100: (((dc[in[1]] & 0xf) << 4) | (dc[in[2]] >> 2));
		out[2] = in[3] == '='? 0x100: ((((dc[in[2]]) & 0x3) << 6) | dc[in[3]]);
	}
	memcpy(s, t, sizeof(t));
	for ( ; t[tl - 1] == 0x100; tl--) {
	}
	return tl;
}
//main
int main() {
#if 1
	freopen(input, "r", stdin);
	//freopen(output, "w", stdout);
#endif
	static int buf[maxn];
	dc_Init();
	while (~scanf("%d", &n)) {
		aca.Init();
		for (int i = 0; i < n; i++) {
			scanf("%s", key);
			for (int j = 0, l = strlen(key); j < l; j++) {
				buf[j] = key[j];
			}
			int bl = decode(buf, strlen(key));
			aca.Insert(i + 1, buf, bl);
		}
		aca.Link();
		scanf("%d", &m);
		while (m--) {
			scanf("%s", ask);
			for (int j = 0, l = strlen(ask); j < l; j++) {
				buf[j] = ask[j];
			}
			int bl = decode(buf, strlen(ask));
			printf("%d\n", aca.Search(buf, bl));
		}
		puts("");
		aca.Free();
	}
	return 0;
}
