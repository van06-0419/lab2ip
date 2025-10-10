#include <gtest/gtest.h>
#include "ip_filter.h"
#include <sstream>
#include <vector>
#include <tuple>

TEST(IPFilterTest, ParseIpTest) {
    std::string input = 
        "192.168.1.1\tother_data\n"
        "10.0.0.1\tmore_data\n"
        "255.255.255.255\tlast\n";
    
    std::istringstream iss(input);
    auto ips = read_and_sort_ips(iss);

    ASSERT_EQ(ips.size(), 3);
    EXPECT_EQ(ips[0], std::make_tuple(255, 255, 255, 255));
    EXPECT_EQ(ips[1], std::make_tuple(192, 168, 1, 1));
    EXPECT_EQ(ips[2], std::make_tuple(10, 0, 0, 1));
}

TEST(IPFilterTest, SortingTest) {
    std::string input = 
        "1.1.1.1\n"
        "2.2.2.2\n"
        "1.1.1.2\n";
    
    std::istringstream iss(input);
    auto ips = read_and_sort_ips(iss);

    ASSERT_EQ(ips.size(), 3);
    EXPECT_EQ(ips[0], std::make_tuple(2, 2, 2, 2));
    EXPECT_EQ(ips[1], std::make_tuple(1, 1, 1, 2));
    EXPECT_EQ(ips[2], std::make_tuple(1, 1, 1, 1));
}

TEST(IPFilterTest, FilterTest) {
    std::vector<std::tuple<int, int, int, int>> test_ips = {
        std::make_tuple(1, 2, 3, 4),
        std::make_tuple(1, 5, 6, 7),
        std::make_tuple(46, 2, 3, 4),
        std::make_tuple(46, 70, 8, 9),
        std::make_tuple(10, 46, 3, 4),
        std::make_tuple(11, 12, 46, 14),
        std::make_tuple(15, 16, 17, 46)
    };

    auto filter1 = filter_first_byte(test_ips, 1);
    EXPECT_EQ(filter1.size(), 2);
    EXPECT_EQ(filter1[0], std::make_tuple(1, 2, 3, 4));
    EXPECT_EQ(filter1[1], std::make_tuple(1, 5, 6, 7));

    auto filter2 = filter_first_two_bytes(test_ips, 46, 70);
    EXPECT_EQ(filter2.size(), 1);
    EXPECT_EQ(filter2[0], std::make_tuple(46, 70, 8, 9));

    auto filter3 = filter_any_byte(test_ips, 46);
    EXPECT_EQ(filter3.size(), 5); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
