#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;
const int inf = 0x8fffffff;

struct splay_t {
	struct node {
		node *p, *s[2];
		int size, key;
		int sum, dsum[2], msum;
		int cover_tag, reverse_tag;
		int side() {
			return p->s[1] == this;
		}
		int rank() {
			return s[0]? 1+s[0]->size: 1;
		}
		node *set_cover(int _key) {
			cover_tag = 1;
			key = _key;
			sum = size*key;
			dsum[0] = dsum[1] = msum = max(sum, key);
			return this;
		}
		node *set_reverse() {
			reverse_tag ^= 1;
			swap(s[0], s[1]);
			swap(dsum[0], dsum[1]);
			return this;
		}
		node *push() {
			for (int i = 0; i < 2; i++) {
				if (!s[i]) continue;
				if (cover_tag) s[i]->set_cover(key);
				if (reverse_tag) s[i]->set_reverse();
			}
			cover_tag = reverse_tag = 0;
			return this;
		}
		node *pull() {
			sum = dsum[0] = dsum[1] = msum = key;
			for (int i = size = 1; ~i; i--) {
				if (!s[i]) continue;
				size += s[i]->size;
				sum += s[i]->sum;
				dsum[i] = max(s[i]->dsum[i], s[i]->sum+key);
				if (s[!i]) {
					dsum[i] = max(dsum[i], s[i]->sum+key+s[!i]->dsum[i]);
					msum = max(msum, s[i]->dsum[!i]+key+s[!i]->dsum[i]);
				} else dsum[!i] = max(s[i]->dsum[!i]+key, key);
				msum = max(msum, s[i]->msum);
				msum = max(msum, s[i]->dsum[!i]+key);
				msum = max(msum, dsum[i]);
			}
			return this;
		}
		node *set(int b, node *x) {
			if (push()->s[b] = x) x->p = this;
			return pull();
		}
		node *get(int b) {
			return push()->s[b];
		}
		node *cut(int b, node *&x) {
			if (x = push()->s[b]) s[b]->p = 0;
			s[b] = 0;
			return pull();
		}
		node *spin() {
			node *y = p->push();
			int b = push()->side();
			if (p = y->p) p->s[y->side()] = this;
			if (y->s[b] = s[!b]) s[!b]->p = y;
			return (s[!b] = y)->pull()->p = this;
		}
		node *fine(node *x = 0) {
			for ( ; p != x; spin())
				if (p->p != x)
					if (side() == p->side()) p->spin();
					else spin();
			return pull();
		}
		node *pick(int k) {
			node *x = this;
			for ( ; x->rank() != k; ) {
				int b = x->rank() < k;
				k -= b*x->rank();
				x = x->get(b);
			}
			return x->fine();
		}
	};
	node *give(node *t = 0) {
		static node *top = 0;
		static int size = 1;
		if (t) t->s[1] = top, top = t;
		else {
			if (!top) {
				top = new node[size<<=1];
				for (int i = 0; i < size-1; i++)
					top[i].s[1] = top+i+1;
				top[size-1].s[1] = 0;
			}
			t = top, top = top->s[1];
		}
		return t;
	}
	node *make(int key) {
		node t = {0, {0}, 1, key, key, {key, key}, key, 0, 0};
		return &(*give() = t);
	}
	void drop(node *&t) {
		if (!t) return ;
		drop(t->s[0]), drop(t->s[1]);
		give(t), t = 0;
	}
	void merge(node *x, node *y, node *&t) {
		if (!x || !y) t = x? x: y;
		else t = x->pick(x->size)->set(1, y);
	}
	void split(node *t, int k, node *&x, node *&y) {
		if (!k) x = 0, y = t;
		else if (t->size == k) x = t, y = 0;
		else x = t->pick(k)->cut(1, y);
	}
	void slice(node *&t, int l = -1, int r = -1) {
		static node *a, *b;
		if (~l) split(t, l-1, a, b), split(b, r-l+1, t, b);
		else merge(t, b, b), merge(a, b, t);
	}
	void show(node *t) {
		if (!t) return ;
		t->push();
		show(t->s[0]);
		printf(" %d", t->key);
		show(t->s[1]);
		t->pull();
	}
};
typedef splay_t::node node;

int get_int() {
  int x = 0, c = getchar(), b = 1;
  for ( ; isspace(c); ) c = getchar();
  if (c == '-') b = -1, c = getchar();
  for ( ; isdigit(c); c = getchar()) x = x*10+c-'0';
  return x*b;
}

splay_t zkl;
int n, m;

int main() {
#if 1
	freopen("input.in", "r", stdin);
#endif
	for ( ; ~scanf("%d%d", &n, &m); ) {
		node *rt = 0;
		for (int i = 0; i < n; i++)
			zkl.merge(rt, zkl.make(get_int()), rt);
		for ( ; m--; ) {
			char op[20];
			scanf("%s", op);
			if (op[2] == 'X') {
				printf("%d\n", rt? rt->msum: 0);
			} else {
				int posi = get_int(), tot = get_int();
				if (*op == 'I') {
					node *x = 0;
					zkl.split(rt, posi, x, rt);
					for (int i = 0; i < tot; i++)
						zkl.merge(x, zkl.make(get_int()), x);
					zkl.merge(x, rt, rt);
				} else {
					zkl.slice(rt, posi, posi+tot-1);
					if (*op == 'D') {
						zkl.drop(rt);
					} else if (*op == 'M') {
						rt->set_cover(get_int());
					} else if (*op == 'R') {
						rt->set_reverse();
					} else if (*op == 'G') {
						printf("%d\n", rt? rt->sum: 0);
					}
					zkl.slice(rt);
				}
			}
		}
	}
	return 0;
}
