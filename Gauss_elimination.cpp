// 수치해석 가우스 소거법
#include <iostream>
#include <cmath>    // abs(), round()
using namespace std;
double aug[4][5], solution[4];  // 3x3 행렬

int main()
{
    cout << "[input]" << endl << "input 3x3 coefficient matrix" << endl;
    for (int i = 1; i <= 3; ++i)    // coefficient matrix (A)
        for (int j = 1; j <= 3; ++j)
            cin >> aug[i][j];
    cout << endl << "input 3 dimension constant vector" << endl;
    for (int i = 1; i <= 3; ++i)    // constant vector (b)
        cin >> aug[i][4];

    int pivot;
    double m, pivot_value = 0;
    for (int i = 1; i <= 3-1; ++i) { // 행
        pivot = i;
        for (int j = i + 1; j <= 3; ++j) {    // 행, partial pivoting
            if (abs(aug[j][i]) > abs(aug[i][i]) && abs(aug[j][i]) > pivot_value) {
                pivot = j;
                pivot_value = abs(aug[j][i]);
            }
        }
        if (aug[pivot][i] == 0) {
            cout << "No unique solution exists" << endl;
            exit(0);
        } else {
            if (pivot != i) {  // row exchange
                for (int k = i; k <= 3+1; ++k) { // 열
                    int tmp = aug[i][k];
                    aug[i][k] = aug[pivot][k];
                    aug[pivot][k] = tmp;
                }
            }
        }
        if (aug[3][3] == 0) {
            cout << "No unique solution exists" << endl;
            exit(0);
        } else {    // four-digit floating-point arithmetic (소수점 4자리)
            for (int j = i + 1; j <= 3; ++j) { // 행
                m = static_cast<double>(aug[j][i]) / aug[i][i] * 10000;
                m = round(m) / 10000.0;
                aug[j][i] = 0;
                for (int p = i + 1; p <= 3+1; ++p) { // 열
                    aug[j][p] -= m * aug[i][p];
                }
            }
        }
    }
    solution[3] = aug[3][3+1] / aug[3][3];  // back substitution
    double sum;
    for (int i = 3-1; i >= 1; --i) {
        sum = 0;
        for (int j = i+1; j <= 3; ++j) {
            sum += aug[i][j] * solution[j];
        }
        solution[i] = (aug[i][3+1] - sum) / aug[i][i];
    }
    
    cout << endl << "[output]" << endl << "row echelon form" << endl;;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 4; ++j) {
            cout << aug[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl << "solution vector" << endl << '[';
    for (int i = 1; i <= 3; ++i) {
        if (i == 3) cout << solution[i];
        else cout << solution[i] << ' ';
    }
    cout << ']' << endl;
    return 0;
}