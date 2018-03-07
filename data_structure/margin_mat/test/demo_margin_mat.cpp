#include "margin_mat.hpp"

int main() {
    MarginMat mat(3, 3, 2, 0);
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            mat(r, c) = r*3+c;
        }
    }
    mat(-1, -1) = 12;
    mat._debug_show();
}
