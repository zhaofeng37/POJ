// POJ 3667 http://poj.org/problem?id=3667
/**
1. Traditional Segment Tree Problem
2. segNode has 6 components.
 - 2.1 l is the left postion of this segment
       r is the right position of this segment
       [l...r] is closed interval
 - 2.2 tl is the total empty room length under 
       this segment node. 
 - 2.3 ll is the maximal empty room length start
       at the leftmost postion
 - 2.4 rl is the maximal empty room length end
       at the leftmost postion
 - 2.5 m has 3 status.
  * -1 means lazy flag is clear. No need to descend 
    flag to children segNode.
  * 0 means room is empty.
  * 1 means room is ouccupied
  * Descend the flag 0 and/or 1 in query&update method
3. build the binary segment tree and fill the content
   of the segNode recursively. The initial m in the segNode
   is 0 which referred to every room is available.
4. query is a recursive method. The core thinking is descend
   the m in root segNode to the left and right children and
   then update them.
 - 4.1 the total empty room count is equal and more than request
       call query recursivly to find the precision position
 - 4.2 the summary of rightmost empty room in left child and 
       leftmost empty room in right child is equal and more than
       request, we find the precision position which is the start
       of the leftmost in left child.
 - 4.3 there is no empty room in hotel now if the upper 3 cases 
       can NOT staisfy the conditions.
5. It is as less as the algorithm need to try to update the
   segNode ll, tl, rl and descend the m in the same time.
 - 5.1 one segNode has only one m status. This implys that m will
       be set to 1 if all room occupied in this node, in contrast
       m would be 0 if all room empty. Otherwise -1 will be found
       in m.
 - 5.2 compare to the thinking of the segment tree, the principle
       of update ll, tl, rl is much easier, see the code
*/
#include <stdio.h>
#include <algorithm>

#define N 50008
#define LC(a) (a << 1)
#define RC(a) (a << 1 | 1)

// [1...X] 闭闭区间
struct segNode {
	int l, r, m, tl, ll, rl;
	int mid() { return (l + r) >> 1; }
	int len() { return r - l + 1; }
	void update() { tl = ll = rl = (m ? 0 : r - l + 1); }
} sn[N * 4];

void build(int rt, int l, int r) {
	sn[rt].l = l; sn[rt].r = r; sn[rt].m = 0;
	sn[rt].ll = sn[rt].rl = sn[rt].tl = sn[rt].len();
	if (l == r) return;
	int mid = sn[rt].mid();
	build(LC(rt), l, mid);
	build(RC(rt), mid + 1, r);
}

int query(int rt, int w) {
	if (sn[rt].l == sn[rt].r && 1 == w)
	    return sn[rt].l;
	if (-1 != sn[rt].m) {
		sn[LC(rt)].m = sn[RC(rt)].m = sn[rt].m;
		sn[rt].m = -1;
		sn[LC(rt)].update();
		sn[RC(rt)].update();
	}
	if (sn[LC(rt)].tl >= w) return query(LC(rt), w);
	if (sn[LC(rt)].rl + sn[RC(rt)].ll >= w) return sn[LC(rt)].r - sn[LC(rt)].rl + 1;
	if (sn[RC(rt)].tl >= w) return query(RC(rt), w);

	return 0;
}

void update(int l, int r, int m, int rt) {
	if (l == sn[rt].l && r == sn[rt].r) {
		sn[rt].m = m;
		sn[rt].update();
		return;
	}
	if (-1 != sn[rt].m) {
		sn[LC(rt)].m = sn[RC(rt)].m = sn[rt].m;
		sn[rt].m = -1;
		sn[LC(rt)].update();
		sn[RC(rt)].update();
	}
	int mid = sn[rt].mid();
	if (l > mid) update(l, r, m, RC(rt));
	else if (r <= mid) update(l, r, m, LC(rt));
	else {
		update(l, mid, m, LC(rt));
		update(mid + 1, r, m, RC(rt));
	}

	sn[rt].tl = std::max(sn[LC(rt)].tl, sn[RC(rt)].tl);
	sn[rt].tl = std::max(sn[rt].tl, (sn[LC(rt)].rl + sn[RC(rt)].ll));
	if (sn[LC(rt)].len() > sn[LC(rt)].ll)
	    sn[rt].ll = sn[LC(rt)].ll;
	else
	    sn[rt].ll = sn[LC(rt)].ll + sn[RC(rt)].ll;
	if (sn[RC(rt)].len() > sn[RC(rt)].rl)
	    sn[rt].rl = sn[RC(rt)].rl;
	else
	    sn[rt].rl = sn[LC(rt)].rl + sn[RC(rt)].rl;

}

int main() {
	int l, r, c, w, idx, io;
	while (~scanf("%d %d", &r, &c)) {
		build(1, 1, r);
		while (c--) {
			scanf("%d", &io);
			if (1 == io) { // ci
			    scanf("%d", &w);
				idx = query(1, w);
				printf("%d\n", idx);
				if (idx) update(idx, idx + w - 1, 1, 1);
			} else { // co
				scanf("%d %d", &l, &w);
				update(l, l + w - 1, 0, 1);
			}
		}
	}
    return 0;
}