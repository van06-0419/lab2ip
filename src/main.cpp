#include <vector>
#include <iostream>
#include <tuple>
#include "ip_filter.h"  // 注意头文件名应该是 ip_filter.h

int main() {
    // 使用正确的数据类型：tuple而不是vector<vector<int>>
    std::vector<std::tuple<int, int, int, int>> test_ips = {
        std::make_tuple(192, 168, 1, 1),
        std::make_tuple(10, 0, 0, 1),
        std::make_tuple(172, 16, 0, 1),
        std::make_tuple(192, 168, 1, 2),
        std::make_tuple(1, 1, 1, 1),
        std::make_tuple(46, 70, 0, 1)
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
