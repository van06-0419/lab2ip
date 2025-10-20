#include "ip_filter.h"
#include <iostream>

int main() {
    // 直接使用硬编码的测试数据
    std::vector<std::vector<int>> test_ips = {
        {192, 168, 1, 1},
        {10, 0, 0, 1},
        {172, 16, 0, 1},
        {192, 168, 1, 2},
        {1, 1, 1, 1},
        {46, 70, 0, 1}
    };
    
    auto ips = test_ips;
    
    std::cout << "所有IP地址:" << std::endl;
    print_ips(ips);
    
    std::cout << "\n第一个字节为1的IP:" << std::endl;
    print_ips(filter_first_byte(ips, 1));
    
    std::cout << "\n第一个字节46且第二个字节70的IP:" << std::endl;
    print_ips(filter_first_two_bytes(ips, 46, 70));
    
    std::cout << "\n任意字节为46的IP:" << std::endl;
    print_ips(filter_any_byte(ips, 46));
    
    return 0;
}
