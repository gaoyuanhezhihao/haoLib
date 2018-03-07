#ifndef MARGIN_MAT_H
#define MARGIN_MAT_H

#include <iostream>
#include <vector>

class MarginMat{
    public:
        MarginMat(const int rows, const int cols,
                const int margin_width, const int init_v);
        int & operator()(const int r, const int c);
        void _debug_show();
    private:
        const int _w;
        std::vector<std::vector<int>> _mat;
};
#endif //MARGIN_MAT_H
