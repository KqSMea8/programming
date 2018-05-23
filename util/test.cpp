#include "processor.h"
#include <iostream>

bool print(const data_t &d)
{
    std::cout << d.type << std::endl;
    return true;
}

int main() {
    processor smt(print, 2);
    smt.start();
    data_t data;

    for (int i = 0; i < 1000; i++) {
        data.type = i;
        smt.add_data(data);
    }
    smt.stop();
  return 0;
}
  
