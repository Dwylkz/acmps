#include <cstdio>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
const int M = 200;

// exact
struct dancing {
#define dfor(c, a, b) for (int c = a[b]; c != b; c = a[c])
  static const int row_size = 220, column_size = 220,
               total_size = row_size*column_size;
  typedef int row[row_size],
          column[column_size],
          total[total_size];
  total l, r, u, d, in_column, in_row;
  bitset<50> use;
  column s;
  int index, current_row, row_head, limit, mx, rn;
  void init(int n, int m) {
    rn = m;
    limit = 0;
    index = ++n;
    for (int i = 0; i < n; i++) {
      l[i] = (i - 1 + n) % n;
      r[i] = (i + 1) % n;
      u[i] = d[i] = i;
    }
    current_row = 0;
    memset(s, 0, sizeof(s));
    use = ans = bitset<50>();
    mx = -1;
  }
  void push(int i, int j) {
    i++; j++;
    if (current_row < i) {
      row_head = l[index] = r[index] = index;
      current_row = i;
    }
    l[index] = l[row_head]; r[index] = row_head;
    r[l[row_head]] = index; l[row_head] = index;
    u[index] = u[j]; d[index] = j;
    d[u[j]] = index; u[j] = index;
    s[j]++;
    in_row[index] = i;
    in_column[index++] = j;
  }
  void exactly_remove(int c) {
    l[r[c]] = l[c];
    r[l[c]] = r[c];
    dfor(i, d, c) {
      dfor (j, r, i) {
        u[d[j]] = u[j];
        d[u[j]] = d[j];
        s[in_column[j]]--;
      }
    }
  }
  void exactly_resume(int c) {
    dfor(i, u, c) {
      dfor(j, l, i) {
        s[in_column[j]]++;
        d[u[j]] = u[d[j]] = j;
      }
    }
    r[l[c]] = l[r[c]] = c;
  }
  bool exactly_dance(int step = 0) {
    limit = max(limit, step);
    if (limit == mx) return 1;
    if (!r[0]) return 0;
    int has = rn-use.count();
    if (!has || step+has < limit || step+has < mx) return 0;
    int x = r[0];
    dfor(i, r, 0) {
      if (s[i] && s[i] < s[x] || !s[x]) {
        x = i;
      }
    }
    exactly_remove(x);
    dfor(i, d, x) {
      use[in_column[i]] = 1;
      dfor(j, r, i) {
        exactly_remove(in_column[j]);
      }
      if (exactly_dance(step + 1)) {
        return 1;
      }
      dfor(j, l, i) {
        exactly_resume(in_column[j]);
      }
      use[in_column[i]] = 0;
    }
    exactly_resume(x);
    return 0;
  }
#undef dfor
};
dancing dlx;

struct com {
  int b, t;
  void input() {
    scanf("%d%d", &b, &t);
  }
} c[M];
int n, m, g[M][50];

int main() {
#if 1
  freopen("input.in", "r", stdin);
#endif
  for ( ; ~scanf("%d%d", &n, &m); ) {
    memset(g, 0, sizeof(g));
    dlx.init(n, m);
    for (int i = 0; i < m; i++) {
      c[i].input();
      if (c[i].b > c[i].t) swap(c[i].b, c[i].t);
      int b = c[i].b, t = c[i].t;
      g[i][b] = g[i][t] = 1;
      dlx.push(i, b-1);
      dlx.push(i, t-1);
    }
    dlx.exactly_dance();
    int limit = dlx.limit;
    vector<int> ans;
    int ban[M] = {0};
    for (int i = 0; i < m; i++) {
      int tm = m;
      memset(ban, 0, sizeof(int)*m);
      for (int j = 0; j < m; j++) if (i != j)
        if (g[j][c[i].b] || g[j][c[i].t]) {
          ban[j] = 1;
          tm--;
        }
      dlx.init(n, tm);
      for (int j = 0; j < m; j++) if (!ban[j]) {
        dlx.push(j, c[j].b-1);
        dlx.push(j, c[j].t-1);
      }
      dlx.mx = limit;
      dlx.exactly_dance();
      if (limit != dlx.limit) ans.push_back(i+1);
    }
    printf("%d\n", (int)ans.size());
    if (!ans.size()) puts("");
    else for (int i = 0; i < ans.size(); i++)
      printf("%d%c", ans[i], i < ans.size()-1? ' ': '\n');
  }
  return 0;
}
