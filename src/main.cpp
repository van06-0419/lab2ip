#include "ip_filter.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream file;

    if (argc > 1) {
        file.open(argv[1]);
        if (file.is_open()) {
            input = &file;
        } else {
            std::cerr << "无法打开文件: " << argv[1] << std::endl;
            return 1;
        }
    }

    auto ips = read_and_sort_ips(*input);

    print_ips(ips);                                 
    print_ips(filter_first_byte(ips, 1));            
    print_ips(filter_first_two_bytes(ips, 46, 70));  
    print_ips(filter_any_byte(ips, 46));             

    if (file.is_open()) {
        file.close();
    }

    return 0;
}
