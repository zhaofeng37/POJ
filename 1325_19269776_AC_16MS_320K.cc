/* POJ1325 Machine Schedule http://poj.org/problem?id=3414
1. This is a minimal vertex cover of bipartite graph problem.
2. the amount of the minimal vertex cover is equal to maximum matching
3. Konig's theorem find the way to determine the amount of
   maximum matching in bipartite graph.
*/

#include <stdio.h>
#include <cstring>

int n, m, k;
const int MAXN = 100;
char map[MAXN + 2][MAXN + 2], linked[MAXN + 2];
char visit[MAXN + 2];

bool findEdge(int x) {
  for (int j = 1; j <= m; ++j) {
    if (map[x][j] && !visit[j]) {
      visit[j] = 1;
      if (!linked[j] || findEdge(linked[j])) {
        linked[j] = x;
        return true;
      }
    }
  }
  return false;
}

int minVertexCover() {
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    memset(visit, 0, sizeof(visit));
    if (findEdge(i)) ++cnt;
  }
  return cnt;
}

int main() {
  int a, b, c;
  while (1) {
    scanf("%d", &n);
    if (0 == n)
      break;

    memset(map, 0, sizeof(map));
    memset(linked, 0,  sizeof(linked));
    scanf("%d %d", &m, &k);
    for (int i = 0; i < k; ++i) {
      scanf("%d %d %d", &a, &b, &c);
      if (b && c) map[b][c] = 1;
    }

    printf("%d\n", minVertexCover());
  }
  return 0;
}