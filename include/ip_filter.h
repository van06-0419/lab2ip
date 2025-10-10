#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <vector>
#include <tuple>
#include <istream>

std::vector<std::tuple<int, int, int, int>> read_and_sort_ips(std::istream& is);

std::vector<std::tuple<int, int, int, int>> filter_first_byte(
    const std::vector<std::tuple<int, int, int, int>>& ips, 
    int value
);

std::vector<std::tuple<int, int, int, int>> filter_first_two_bytes(
    const std::vector<std::tuple<int, int, int, int>>& ips, 
    int first, 
    int second
);

std::vector<std::tuple<int, int, int, int>> filter_any_byte(
    const std::vector<std::tuple<int, int, int, int>>& ips, 
    int value
);

void print_ips(const std::vector<std::tuple<int, int, int, int>>& ips);

#endif // IP_FILTER_H
