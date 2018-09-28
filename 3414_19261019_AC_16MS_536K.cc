/* POJ3414 Pots http://poj.org/problem?id=3414
1. This is a Breath-First-Search Visit-Tree problem.
2. The node in the visit-tree store the status of liters of the
   2 pots, the amount of current operation from origin and the
   detail path.
3. visit array store the status whether the liters had been visited.
   if visited we will go on processing in a moment, in contrast we
   will try to do the 6 operations if needed and refresh the visit
   array and push the new node in the queue using BFS.
*/

#include <stdio.h>
#include <queue>
#include <cstring>

int a, b, c;
const int MAXN = 100;

const char *op[] = {
    "FILL(1)",
    "FILL(2)",
    "DROP(1)",
    "DROP(2)",
    "POUR(1,2)",
    "POUR(2,1)",
};

struct node {
    int a, b;
    int level;
    char path[MAXN + 1];
};

char visit[MAXN + 1][MAXN + 1];

void printOperation(node& leaf) {
    printf("%d\n", leaf.level);
    for (int i = 0; i < leaf.level;  ++i) {
        printf("%s\n", op[leaf.path[i]]);
    }
}

void bfs() {
    std::queue<node> q;
    memset(&visit, 0, sizeof(visit));
    node root;
    root.a = 0; root.b = 0; root.level = 0;
    q.push(root);
    visit[0][0] = 1;

    while (!q.empty()) {
        root = q.front();
        q.pop();

        if (c == root.a || c == root.b) {
            printOperation(root);
            return;
        }

        node leaf = root;
        leaf.level++;

        // FILL(1) ==> 0
        if (root.a < a) {
            leaf.a = a;
            leaf.b = root.b;
            if (false == visit[leaf.a][leaf.b]) {
                leaf.path[root.level] = 0;
                q.push(leaf);
                visit[leaf.a][leaf.b] = 1;
            }
        }

        // FILL(2) ==> 1
        if (root.b < b) {
            leaf.a = root.a;
            leaf.b = b;
            if (false == visit[leaf.a][leaf.b]) {
                leaf.path[root.level] = 1;
                q.push(leaf);
                visit[leaf.a][leaf.b] = 1;
            }
        }

        // DROP(1) ==> 2
        if (root.a) {
            leaf.a = 0;
            leaf.b = root.b;
            if (false == visit[leaf.a][leaf.b]) {
                leaf.path[root.level] = 2;
                q.push(leaf);
                visit[leaf.a][leaf.b] = 1;
            }
        }

        // DROP(2) ==> 3
        if (root.b) {
            leaf.a = root.a;
            leaf.b = 0;
            if (false == visit[leaf.a][leaf.b]) {
                leaf.path[root.level] = 3;
                q.push(leaf);
                visit[leaf.a][leaf.b] = 1;
            }
        }

        // POUR(1,2) ==> 4
        if (root.a && root.b < b) {
            if (root.a < b - root.b) {
                leaf.a = 0;
                leaf.b = root.b + root.a;
            } else {
                leaf.a = root.a - (b - root.b);
                leaf.b = b;
            }
            if (false == visit[leaf.a][leaf.b]) {
                leaf.path[root.level] = 4;
                q.push(leaf);
                visit[leaf.a][leaf.b] = 1;
            }
        }

        // POUR(2,1) ==> 5
        if (root.b && root.a < a) {
            if (root.b < a - root.a) {
                leaf.b = 0;
                leaf.a = root.a + root.b;
            } else {
                leaf.b = root.b - (a - root.a);
                leaf.a = a;
            }
            if (false == visit[leaf.a][leaf.b]) {
                leaf.path[root.level] = 5;
                q.push(leaf);
                visit[leaf.a][leaf.b] = 1;
            }
        }
    }
    printf("impossible\n");
}

int main() {
    while (~scanf("%d %d %d", &a, &b, &c))
        bfs();
    return 0;
}
