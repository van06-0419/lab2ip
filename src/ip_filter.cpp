#include "ip_filter.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::tuple<int, int, int, int>> read_and_sort_ips(std::istream& is) {
    std::vector<std::tuple<int, int, int, int>> ips;
    std::string line;

    while (std::getline(is, line)) {
        size_t tab_pos = line.find('\t');
        std::string ip_str = (tab_pos != std::string::npos) ? 
                            line.substr(0, tab_pos) : line;

        std::vector<std::string> parts = split(ip_str, '.');
        if (parts.size() != 4) {
            continue;
        }

        try {
            int b1 = std::stoi(parts[0]);
            int b2 = std::stoi(parts[1]);
            int b3 = std::stoi(parts[2]);
            int b4 = std::stoi(parts[3]);
            
            if (b1 >= 0 && b1 <= 255 &&
                b2 >= 0 && b2 <= 255 &&
                b3 >= 0 && b3 <= 255 &&
                b4 >= 0 && b4 <= 255) {
                ips.emplace_back(b1, b2, b3, b4);
            }
        } catch (...) {
            continue;
        }
    }

    std::sort(ips.begin(), ips.end(), 
        [](const std::tuple<int, int, int, int>& a, 
           const std::tuple<int, int, int, int>& b) {
            return a > b;
        }
    );

    return ips;
}

std::vector<std::tuple<int, int, int, int>> filter_first_byte(
    const std::vector<std::tuple<int, int, int, int>>& ips, 
    int value
) {
    std::vector<std::tuple<int, int, int, int>> result;
    std::copy_if(ips.begin(), ips.end(), std::back_inserter(result),
        [value](const std::tuple<int, int, int, int>& ip) {
            return std::get<0>(ip) == value;
        }
    );
    return result;
}

std::vector<std::tuple<int, int, int, int>> filter_first_two_bytes(
    const std::vector<std::tuple<int, int, int, int>>& ips, 
    int first, 
    int second
) {
    std::vector<std::tuple<int, int, int, int>> result;
    std::copy_if(ips.begin(), ips.end(), std::back_inserter(result),
        [first, second](const std::tuple<int, int, int, int>& ip) {
            return std::get<0>(ip) == first && std::get<1>(ip) == second;
        }
    );
    return result;
}

std::vector<std::tuple<int, int, int, int>> filter_any_byte(
    const std::vector<std::tuple<int, int, int, int>>& ips, 
    int value
) {
    std::vector<std::tuple<int, int, int, int>> result;
    std::copy_if(ips.begin(), ips.end(), std::back_inserter(result),
        [value](const std::tuple<int, int, int, int>& ip) {
            return std::get<0>(ip) == value ||
                   std::get<1>(ip) == value ||
                   std::get<2>(ip) == value ||
                   std::get<3>(ip) == value;
        }
    );
    return result;
}

void print_ips(const std::vector<std::tuple<int, int, int, int>>& ips) {
    for (const auto& ip : ips) {
        std::cout << std::get<0>(ip) << "."
                  << std::get<1>(ip) << "."
                  << std::get<2>(ip) << "."
                  << std::get<3>(ip) << std::endl;
    }
}
