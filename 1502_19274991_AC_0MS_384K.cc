// POJ1502 MPI Maelstrom http://poj.org/problem?id=1502
/**
No more skills than traditional Dijkstra's algorithm
*/

#include <stdio.h>
#include <limits.h>
#include <cstring>

const int MAXN = 100;
int adjMatrix[MAXN + 4][MAXN + 4], dis[MAXN + 4];
char vertex[MAXN + 4];
int N;

void minDisVertex(int fresh) {
    vertex[fresh] = 1;
    for (int i = 0; i < N; ++i) {
        if (INT_MAX != adjMatrix[i][fresh] && dis[fresh] + adjMatrix[i][fresh] < dis[i])
            dis[i] = dis[fresh] + adjMatrix[i][fresh];
    }

    // find new min distance
    int minDis = INT_MAX;
    int minVtx = 0;
    for (int i = 0; i < N; ++i) {
        if (dis[i] < minDis && 0 == vertex[i]) {
            minDis = dis[i];
            minVtx = i;
        }
    }
    if (INT_MAX != minDis)
        minDisVertex(minVtx);
}

int dijkstra() {
    memset(dis, 0, sizeof(dis));
    memset(vertex, 0, sizeof(vertex));

    for (int i = 0; i < N; ++i)
        dis[i] = adjMatrix[i][0];
    minDisVertex(0);

    int m = 0;
    for (int i = 0; i < N; ++i) {
        if (dis[i] > m)
            m = dis[i];
    }
    return m;
}

int main() {
    char x;
    int weight;
    memset(adjMatrix, 0, sizeof(adjMatrix));
    while (~scanf("%d", &N)) {
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (1 == scanf("%d", &weight)) {
                    adjMatrix[i][j] = weight;
                    adjMatrix[j][i] = weight;
                } else {
                    scanf("%c", &x);
                    adjMatrix[i][j] = INT_MAX;
                    adjMatrix[j][i] = INT_MAX;
                }
            }
        }
        printf("%d\n", dijkstra());
    }
    return 0;
}