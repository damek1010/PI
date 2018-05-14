#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX / 2;

typedef struct Segment {
    int town, travel_time;
} Segment;

typedef struct Line {
    Segment* segments;
    int number, length, start_town;
} Line;

Line* newLine(int number, int length, int start_town) {
    Line* l = new Line;
    l->number = number;
    l->length = length;
    l->start_town = start_town;
    l->segments = new Segment[length];
    return l;
}

typedef struct Node {
    int town, id;
    vector< pair<Node*, int> > neighbours;
} Node;

int** calculateTimesMatrix(Line** lines, int lines_no, int towns) {
    // put your code here
    int** D = new int*[towns];
    for (int i = 0; i < towns; i++) {
        D[i] = new int[towns];
        for (int j = 0; j < towns; j++) {
            D[i][j] = INF;
            if (i == j) D[i][j] = 0;
        }
    }

    for (int i = 0; i < lines_no; i++) {
        D[lines[i]->start_town][lines[i]->segments[0].town] = lines[i]->segments[0].travel_time;
        for (int j = 0; j < lines[i]->length - 1; j++) {
            D[lines[i]->segments[j].town][lines[i]->segments[j + 1].town] = lines[i]->segments[j + 1].travel_time;
        }
    }

    for (int k = 0; k < towns; k++)
      for (int i = 0; i < towns; i++) {
          for (int j = 0; j < towns; j++) {
              D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
          }
      }

    for (int i = 0; i < towns; i++) {
        for (int j = 0; j < towns; j++) {
            if (D[i][j] == INF) cout << setw(4) <<  -1 << " ";
            else cout << setw(4) << D[i][j] << " ";
        }
        cout << endl;
    }
    return D;
}

int main() {
    int towns, lines_no, queries;
    cin >> towns >> lines_no >> queries;
    Line** lines = new Line*[lines_no];
    for (int i=0; i<lines_no; i++) {
        int len, start;
        cin >> len >> start;
        lines[i] = newLine(i, len-1, start);
        for (int j=0; j<len-1; j++) {
            int next, time;
            cin >> time >> next;
            lines[i]->segments[j].town = next;
            lines[i]->segments[j].travel_time = time;
        }
    }

    // for (int i = 0; i < lines_no; i++) {
    //     for (int j = 0; j < lines_no; j++)
    //         cout << lines[i][j] << " ";
    //     cout << endl;
    // }
    // return 0;
    int** times = calculateTimesMatrix(lines, lines_no, towns);

    for (int i=0; i<queries; i++) {
        int u, v;
        cin >> u >> v;
        cout << times[u][v] << endl;
    }

    for (int i=0; i<towns; i++) delete[] times[i];
    delete[] times;
    for (int i=0; i<lines_no; i++) {
        delete[] lines[i]->segments;
        delete lines[i];
    }
    delete[] lines;
}
