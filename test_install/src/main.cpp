#include <iostream>
#include "config/Config.hpp"
//#include "Config.hpp"

int main(int argc, const char ** argv) {
    configs.init_by_string("a=1\n");
    cout << string(get_param("c")) << endl;
    //cout << string(configs["c"]) << endl;
}
