#include <iostream>
#include "margin_mat.hpp"

using namespace std;
MarginMat::MarginMat(const int rows, const int cols,
        const int margin_width, const int init_v):_w(margin_width),\
        _mat(rows+2*margin_width, std::vector<int>(cols+2*margin_width, init_v)){}

int &  MarginMat::operator()(const int r, const int c) {
    return _mat[r+_w][c+_w];
}
void MarginMat::_debug_show() {
    for(std::vector<int> & row: _mat) {
        for(int v: row) {
            cout << v  << " ";
        }
        cout << "\n";
    }
}

