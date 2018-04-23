#include <iostream>
using namespace std;

typedef struct point {
    int x, y;
} point;

typedef struct neighbours {
    int n;
    point elems[4];
} neighbours;

neighbours get_neighbours(int** labyrinth, int n, int m, point* p) {
    // find (if exist) all neighbours of point p
        // (consider points: one above p, one below p, one on the left site and one on the right site)
    // use defined structures
    neighbours n;
    point* q;
    n.n = -1;
    n.elems = {NULL, NULL, NULL, NULL}
    if (p->y - 1 > 0) {
      if (labyrinth[p->x][p->y - 1]) {
        q->x = p->x;
        q->y = p->y - 1;
        n.elems[0] = q;
      }
    }
    if (p->y + 1 < m) {
      if (labyrinth[p->x][p->y + 1]) {
        q->x = p->x;
        q->y = p->y + 1;
        n.elems[1] = q;
      }
    }
    if (p->x - 1 > 0) {
      if (labyrinth[p->x - 1][p->y]) {
        q->x = p->x - 1;
        q->y = p->y;
        n.elems[2] = q;
      }
    }
    if (p->y + 1 < n) {
      if (labyrinth[p->x + 1][p->y]) {
        q->x = p->x;
        q->y = p->y;
        n.elems[3] = q;
      }
    }
    return n;
}

bool dfs(int** graph, int n, int m, bool** visited, point p, point end) {
    // if p is already at the end - return true
    if (p == end) return true;
    // mark p visited
    visited[p->x][p->y] = true;
    // call recursively on every unvisited neighbour
    neighbours n = get_neighbours(graph, n, m, p);
    for (int i = 0; i < 4; i++) {
      if (!visited[n.elems[i]->x][n.elems[i]->y])
        dfs(graph, n, m, visited, n.elems[i], end);
    }
    // if all calls finished fruitlessly - you didn't find exit
    return false;
}


int main() {
    int n, m;
    cin >> n;
    cin >> m;
    int **labyrinth = new int*[n];
    for(int i=0; i<n; i++) labyrinth[i] = new int[m];
    bool** visited = new bool*[n];
    for(int i=0; i<n; i++) visited[i] = new bool[m];

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> labyrinth[i][j];
        }
    }
    point start, end;
    cin >> start.x;
    cin >> start.y;
    cin >> end.x;
    cin >> end.y;
    cout << (dfs(labyrinth, n, m, visited, start, end) ? "TAK" : "NIE") << endl;
}
