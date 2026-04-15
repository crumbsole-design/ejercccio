#include "file_reader.h"
#include <iostream>
#include <fstream>
int main() {
    std::ofstream ofs("test_numbers.txt");
    ofs << "1.5 2.0\n-3.14e2 abc 4.5";
    ofs.close();
    auto v = read_real_numbers_from_file("test_numbers.txt");
    for (double d : v) std::cout << d << "\n";
    return 0;
}
