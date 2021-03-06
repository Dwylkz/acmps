#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define _pb push_back
const int N = 1e5+10;

struct edge_t {
  int v, to;
};
vector<edge_t> E;
int L[N];
void init() {
  E.clear();
  memset(L, -1, sizeof(L));
}
void add(int u, int v) {
  edge_t t = {v, L[u]};
  L[u] = E.size();
  E.push_back(t);
}

int n, m;

int d[N];
void dfs(int u, int dep, int p) {
  d[u] = dep;
  for (int e = L[u]; ~e; e = E[e].to)
    if (e != p) dfs(E[e].v, dep+1, e^1);
}
vector<int> tag;
void bfs() {
  vector<int> q;
  for (int i = 0; i < tag.size(); i++) {
    d[tag[i]] = 0;
    q._pb(tag[i]);
  }
  tag.clear();
  for (int h = 0; h < q.size(); h++) {
    int u = q[h];
    for (int e = L[u]; ~e; e = E[e].to) {
      int v = E[e].v;
      if (d[v] > d[u]+1) {
        d[v] = d[u]+1;
        q._pb(v);
      }
    }
  }
}

int main() {
#if 1
  freopen("input.in", "r", stdin);
#endif
  for ( ; ~scanf("%d%d", &n, &m); ) {
    init();
    for (int u, v, i = 0; i < n-1; i++) {
      scanf("%d%d", &u, &v);
      add(u, v), add(v, u);
    }
    dfs(1, 0, -1);
    tag.clear();
    for ( ; m--; ) {
      int op, x;
      scanf("%d%d", &op, &x);
      if (op == 1) tag._pb(x);
      else {
        bfs();
        printf("%d\n", d[x]);
      }
    }
  }
  return 0;
}
