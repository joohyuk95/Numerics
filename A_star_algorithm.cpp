/*
A* 알고리즘 2차원 배열 격자판에서 구현하기
0 : 갈 수 있는 곳, 1 : 벽 (갈 수 없는 곳)
격자판은 모든 가중치 무방향 그래프이고 모든 가중치가 1임
이동은 인접한 사각형 모두 가능한 것으로 한다. 8 boxes

실수 처리하기 귀찮으니가 휴리스틱 함수는 manhattan distance로 하자.
그래프 그려보기-> matplotlib 쓰자 걍

f(x) = g(x) + h(x)
*/

#include <iostream>
#include <vector>
#include <queue>
#define SIZE 12
using namespace std;

int s_row = 6, s_col = 2;
int e_row = 6, e_col = 10;

int drow[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 아래부터 반시계 방향
int dcol[] = {0, 1, 1, 1, 0, -1, -1, -1};
int G[SIZE][SIZE];
int H[SIZE][SIZE];
vector<vector<pair<int, int> > > parent(SIZE, vector<pair<int, int> > (SIZE));

int Manhattan(int row, int col)
{
    int res = 0;
    if (e_row - row > 0) res += e_row - row;
    else res += row - e_row;

    if (e_col - col > 0) res += e_col - col;
    else res += col - e_col;

    return res;
}

class Info {
public:
    int row, col;
    int F;
    bool operator<(const Info &rhs) const {
        return this->F > rhs.F;
    }
};

priority_queue<Info> open;
queue<Info> close;

int main()
{
    vector<vector<int> > map(12, vector<int> (12));
    for (int i = 3; i <= 9; ++i) {
        map[i][7] = 1;
        if (4 <= i && i <= 6) map[6][i] = 1;
    }

    close.push({s_row, s_col, 0});
    parent[s_row][s_col] = {-1, -1};
    G[s_row][s_col] = 0;

    for (int i = 0; i < 8; ++i) {
        auto cur = close.back();
        int row = cur.row + drow[i];
        int col = cur.col + dcol[i];
        parent[row][col] = {cur.row, cur.col};
        G[row][col] = G[cur.row][cur.col] + 1;
        H[row][col] = Manhattan(row, col);
        int F = G[row][col] + H[row][col];
        open.push({row, col, F}); 
    }
    return 0;
}